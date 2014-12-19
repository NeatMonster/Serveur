#ifndef __Serveur__Server__
#define __Serveur__Server__

#include "ChatMessage.h"
#include "CommandManager.h"
#include "CommandSender.h"
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

    static NetworkManager *getNetwork();

    static Player *getPlayer(string_t);

    static std::unordered_set<Player*> getPlayers();

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
    NetworkManager *network;
    bool running;
    long_t ticks;
    World *world;
    std::unordered_set<Player*> players;

    void run();
};

#endif /* defined(__Serveur__Server__) */
