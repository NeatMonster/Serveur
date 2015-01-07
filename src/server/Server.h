#ifndef __Serveur__Server__
#define __Serveur__Server__

#include "ChatMessage.h"
#include "CommandManager.h"
#include "CommandSender.h"
#include "ConfigManager.h"
#include "Database.h"
#include "NetworkManager.h"
#include "Types.h"

#include <unordered_set>

class Player;
class World;

class Server : public CommandSender {
public:
    static Server *getServer();

    static void broadcast(ChatMessage&);

    static CommandManager *getCommands();

    static ConfigManager *getConfig();

    static Database *getDatabase();

    static NetworkManager *getNetwork();

    static Player *getPlayer(string_t);

    static const std::unordered_set<Player*> &getPlayers();

    Server();

    virtual ~Server();

    void stop();

    void addPlayer(Player*);

    void removePlayer(Player*);

    string_t getName();

    World *getWorld();

    void sendMessage(ChatMessage&);

private:
    static Server *instance;
    CommandManager *commands;
    ConfigManager *config;
    Database *database;
    NetworkManager *network;
    bool running;
    long_t ticks;
    World *world;
    std::unordered_set<Player*> players;

    void run();
};

#endif /* defined(__Serveur__Server__) */
