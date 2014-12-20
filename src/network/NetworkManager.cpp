#include "NetworkManager.h"

#include "Logger.h"
#include "PacketKeepAlive.h"
#include "Player.h"
#include "Server.h"

#include <chrono>

using namespace std::chrono;
typedef std::chrono::high_resolution_clock Clock;

NetworkManager::NetworkManager() : running(false), ticks(0) {
    random = random_t(duration_cast<milliseconds>(Clock::now().time_since_epoch()).count());
}

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
        Logger() << "Démarrage du serveur sur " << ip << ":" << port << std::endl;
        running = true;
        thread = std::thread(&NetworkManager::run, this);
        return true;
    } catch (const ServerSocket::SocketBindException &e) {
        Logger(LogLevel::WARNING) << "IMPOSSIBLE DE SE LIER À L'IP ET AU PORT !" << std::endl;
        Logger(LogLevel::WARNING) << "L'erreur rencontrée est : " << e.what() << std::endl;
        Logger(LogLevel::WARNING) << "Peut-être qu'un serveur occupe déjà ce port ?" << std::endl;
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
    if (ticks++ % 40 == 0) {
        keepAliveId = random();
        for (Player *const &player : Server::getPlayers())
            player->sendPacket(new PacketKeepAlive(keepAliveId));
    }
}

void NetworkManager::run() {
    while (running) {
        try {
            ClientSocket *clientSocket = socket->accept();
            Logger() << "</" << clientSocket->getIP() << ":" <<
                clientSocket->getPort() << " <-> Serveur> s'est connecté" << std::endl;
            connects.push_back(new PlayerConnection(clientSocket));
        } catch (const ServerSocket::SocketAcceptException &e) {}
    }
}
