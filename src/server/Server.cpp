#include "Server.h"

#include "Logger.h"

using namespace std::chrono;
typedef std::chrono::high_resolution_clock Clock;

int main() {
    new Server();
    return 0;
}

Server *Server::getServer() {
    return instance;
}

NetworkManager *Server::getNetwork() {
    return getServer()->network;
}

Server::Server() : running(true), ticks(0) {
    instance = this;
    Logger::info() << "Démarrage du serveur version 1.8.1" << std::endl;
    network = new NetworkManager();
    if (network->start()) {
        run();
        network->stop();
    }
}

Server::~Server() {
    delete network;
}

void Server::stop() {
    running = false;
    Logger::info() << "Extinction du serveur" << std::endl;
}

Server *Server::instance;

void Server::run() {
    Clock::time_point lastTick = Clock::now();
    microseconds correct(0);
    microseconds missed(0);
    while (running) {
        ++ticks;
        network->handlePackets();
        microseconds limit = duration_cast<microseconds>(milliseconds(50) - missed);
        microseconds elapsed = duration_cast<microseconds>(Clock::now() - lastTick);
        if (elapsed < limit) {
            microseconds request = limit - elapsed;
            Clock::time_point start = Clock::now();
            std::this_thread::sleep_for(request - correct);
            Clock::time_point end = Clock::now();
            correct += duration_cast<microseconds>(end - start - request);
            missed = microseconds(0);
        } else {
            missed = elapsed - limit;
            Logger::warning() << "Impossible de suivre. Peut-être que le serveur est surchargé ?" << std::endl;
        }
        lastTick = Clock::now();
    }
}
