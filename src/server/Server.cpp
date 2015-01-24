#include "Server.h"

#include "Block.h"
#include "EntityPlayer.h"
#include "Item.h"
#include "Logger.h"
#include "PacketChatMessage.h"
#include "Types.h"
#include "World.h"

#include <chrono>

using namespace std::chrono;
typedef std::chrono::high_resolution_clock Clock;

int main(int argc, char* argv[]) {
    ushort_t port = 25566;
    for (int i = 1; i < argc; i++) {
        string_t arg = string_t(argv[i]);
        if (arg == "-h" || arg == "--help") {
            std::cout << "Usage : " << string_t(argv[0]) << " [options]" << std::endl;
            std::cout << "Options : " << std::endl;
            std::cout << "\t-h,--help\t\tAffiche l'aide" << std::endl;
            std::cout << "\t-p,--port\t\tSpécifie le port" << std::endl;
            return 0;
        } else if (arg == "-p" || arg == "--port") {
            try {
                port = std::stoi(string_t(argv[++i]));
            } catch (const std::exception &e) {
                std::cout << "Le port spécifié est invalide" << std::endl;
                return 0;
            }
        } else {
            std::cout << "Option '" << arg << "' non reconnue." << std::endl;
            return 0;
        }
    }
    delete new Server(port);
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

Server::Server(ushort_t port) : running(true), ticks(0) {
    instance = this;
    Logger() << "Démarrage du serveur version 1.8.1" << std::endl;
    Block::registerBlocks();
    CreativeTabs::registerTabs();
    Item::registerItems();
    commands = new CommandManager();
    database = new Database();
    network = new NetworkManager();
    world = new World("world");
    if (database->run() && network->start(port)) {
        database->addServer(port);
        run();
        database->removeServer();
        network->stop();
    }
}

Server::~Server() {
    Item::deregisterItems();
    CreativeTabs::deregisterTabs();
    Block::deregisterBlocks();
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
