#include "Server.h"

#include "Logger.h"
#include "PacketChatMessage.h"
#include "Player.h"
#include "World.h"

#include <chrono>

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
    return instance->network;
}

World *Server::getWorld() {
    return instance->world;
}

Player *Server::getPlayer(string_t name) {
    for (Player *const &player : instance->players)
        if (player->getName() == name)
            return player;
    return nullptr;
}

std::set<Player*> Server::getPlayers() {
    return instance->players;
}

void Server::broadcast(ChatMessage &message) {
    for (Player *const &player : instance->players)
        player->sendMessage(message);
}

Server::Server() : running(true), ticks(0) {
    instance = this;
    Logger::info() << "Démarrage du serveur version 1.8.1" << std::endl;
    network = new NetworkManager();
    world = new World("world");
    if (network->start()) {
        run();
        network->stop();
    }
}

Server::~Server() {
    delete network;
    delete world;
}

void Server::stop() {
    running = false;
    Logger::info() << "Extinction du serveur" << std::endl;
}

void Server::addPlayer(Player *player) {
    players.insert(player);
    broadcast(Chat() << Color::YELLOW << player->getName() << " a rejoint la partie");
}

void Server::removePlayer(Player *player) {
    players.erase(player);
    broadcast(Chat() << Color::YELLOW << player->getName() << " a quitté la partie");
}

Server *Server::instance;

void Server::run() {
    Clock::time_point lastTick = Clock::now();
    microseconds correct(0);
    microseconds missed(0);
    while (running) {
        ++ticks;
        network->handlePackets();
        world->onTick();
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
