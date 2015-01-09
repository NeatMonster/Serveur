#include "Server.h"

#include "EntityPlayer.h"
#include "Logger.h"
#include "PacketChatMessage.h"
#include "World.h"

#include <chrono>

using namespace std::chrono;
typedef std::chrono::high_resolution_clock Clock;

int main() {
    delete new Server();
    return 0;
}

Server *Server::getServer() {
    return instance;
}

void Server::broadcast(ChatMessage &message) {
    for (EntityPlayer *const &player : instance->players)
        player->sendMessage(message);
}

CommandManager *Server::getCommands() {
    return instance->commands;
}

Database *Server::getDatabase() {
    return instance->database;
}

NetworkManager *Server::getNetwork() {
    return instance->network;
}

EntityPlayer *Server::getPlayer(string_t name) {
    for (EntityPlayer *const &player : instance->players)
        if (player->getName() == name)
            return player;
    return nullptr;
}

const std::unordered_set<EntityPlayer*> &Server::getPlayers() {
    return instance->players;
}

Server::Server() : running(true), ticks(0) {
    instance = this;
    Logger() << "Démarrage du serveur version 1.8.1" << std::endl;
    commands = new CommandManager();
    database = new Database();
    network = new NetworkManager();
    world = new World("world");
    if (database->run() && network->start()) {
        run();
        network->stop();
    }
}

Server::~Server() {
    delete commands;
    delete database;
    delete network;
    delete world;
}

void Server::stop() {
    running = false;
    Logger() << "Extinction du serveur" << std::endl;
}

void Server::addPlayer(EntityPlayer *player) {
    players.insert(player);
}

void Server::removePlayer(EntityPlayer *player) {
    players.erase(player);
}

string_t Server::getName() {
    return "Serveur";
}

World *Server::getWorld() {
    return world;
}

void Server::sendMessage(ChatMessage &message) {
    Logger() << message.getText() << std::endl;
}

Server *Server::instance;

void Server::run() {
    Clock::time_point lastTick = Clock::now();
    microseconds correct(0);
    microseconds missed(0);
    while (running) {
        ++ticks;
        commands->handleCommands();
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
            Logger(LogLevel::WARNING) << "Impossible de suivre. Peut-être que le serveur est surchargé ?" << std::endl;
        }
        lastTick = Clock::now();
    }
}
