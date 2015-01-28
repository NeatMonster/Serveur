#include "NetworkManager.h"

#include "EntityPlayer.h"
#include "Logger.h"
#include "PacketKeepAlive.h"
#include "Server.h"

#include <chrono>

using namespace std::chrono;
typedef std::chrono::high_resolution_clock Clock;

NetworkManager::NetworkManager() : running(false), ticks(0), socket(nullptr) {
    random = Random(duration_cast<milliseconds>(Clock::now().time_since_epoch()).count());
}

NetworkManager::~NetworkManager() {
    for (PlayerConnection *&connect : connects)
        delete connect;
    if (socket != nullptr)
        delete socket;
}

varint_t NetworkManager::getKeepAliveId() {
    return keepAliveId;
}

bool NetworkManager::start(ushort_t port) {
    try {
        socket = new ServerSocket(Socket::SocketAddress("0.0.0.0", port));
        socket->open();
        Logger() << "Démarrage du serveur sur le port " << port << std::endl;
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
        connect->disconnect("Serveur fermé");
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
        std::shared_ptr<PacketKeepAlive> packet = std::make_shared<PacketKeepAlive>(keepAliveId);
        for (EntityPlayer *player : Server::getPlayers())
            player->sendPacket(packet);
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
