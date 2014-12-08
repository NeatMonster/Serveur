#include "NetworkManager.h"

#include "Logger.h"
#include "PacketKeepAlive.h"
#include "Player.h"
#include "Server.h"

#include <chrono>

using namespace std::chrono;
typedef std::chrono::high_resolution_clock Clock;

NetworkManager::NetworkManager() : running(false) {}

NetworkManager::~NetworkManager() {
    for (PlayerConnection *&connect : connects)
        delete connect;
    delete socket;
}

varint_t NetworkManager::getKeepAliveId() {
    return keepAliveId;
}

bool NetworkManager::start() {
    string_t ip = "0.0.0.0";
    ushort port = 25566;
    try {
        socket = new ServerSocket(Socket::SocketAddress(ip, port));
        socket->open();
        Logger::info() << "Démarrage du serveur sur " << ip << ":" << port << std::endl;
        running = true;
        thread = std::thread(&NetworkManager::run, this);
        keepAliveThread = std::thread(&NetworkManager::runKeepAlive, this);
        return true;
    } catch (const ServerSocket::SocketBindException &e) {
        Logger::warning() << "IMPOSSIBLE DE SE LIER À L'IP ET AU PORT !" << std::endl;
        Logger::warning() << "L'erreur rencontrée est : " << e.what() << std::endl;
        Logger::warning() << "Peut-être qu'un serveur occupe déjà ce port ?" << std::endl;
    }
    return false;
}

bool NetworkManager::stop() {
    for (PlayerConnection *&connect : connects) {
        connect->disconnect("Serveur en cours d'extinction");
        connect->close();
        connect->join();
    }
    running = false;
    socket->close();
    thread.join();
    return true;
}

void NetworkManager::handlePackets() {
    for (auto connect = connects.end(); connect != connects.begin();) {
        connect--;
        if ((*connect)->isClosed()) {
            (*connect)->join();
            delete *connect;
            connect = connects.erase(connect);
        }
    }
    for (PlayerConnection *&connect : connects)
        connect->handlePackets();
}

void NetworkManager::runKeepAlive() {
    random_t rand = random_t(duration_cast<milliseconds>(Clock::now().time_since_epoch()).count());
    while (running) {
        keepAliveId = rand();
        for (Player *const &player : Server::getPlayers())
            player->sendPacket(new PacketKeepAlive(keepAliveId));
        std::this_thread::sleep_for(seconds(2));
    }
}

void NetworkManager::run() {
    while (running) {
        try {
            ClientSocket *clientSocket = socket->accept();
            Logger::info() << "/" << clientSocket->getIP() << ":" <<
                clientSocket->getPort() << " s'est connecté" << std::endl;
            connects.push_back(new PlayerConnection(clientSocket));
        } catch (const ServerSocket::SocketAcceptException &e) {}
    }
}
