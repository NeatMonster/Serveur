#include "NetworkManager.h"

#include "Logger.h"

NetworkManager::NetworkManager() : running(false) {}

NetworkManager::~NetworkManager() {
    for (PlayerConnection *connect : connects)
        delete connect;
    delete socket;
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
    for (PlayerConnection *connect : connects)
        connect->handlePackets();
}

bool NetworkManager::start() {
    string_t ip = "127.0.0.1";
    ushort port = 25566;
    try {
        socket = new ServerSocket(Socket::SocketAddress(ip, port));
        socket->open();
        Logger::info() << "Démarrage du serveur sur " << ip << ":" << port << std::endl;
        running = true;
        thread = std::thread(&NetworkManager::run, this);
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
