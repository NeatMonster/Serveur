#ifndef __Serveur__Server__
#define __Serveur__Server__

#include "ChatMessage.h"
#include "NetworkManager.h"

#include <set>

class Player;
class World;

class Server {
public:
    static Server *getServer();

    static NetworkManager *getNetwork();

    static World *getWorld();

    static Player *getPlayer(string_t);

    static std::set<Player*> getPlayers();

    static void broadcast(ChatMessage&);

    Server();

    ~Server();

    void stop();

    void addPlayer(Player*);

    void removePlayer(Player*);

private:
    static Server *instance;
    NetworkManager *network;
    bool running;
    long_t ticks;
    World *world;
    std::set<Player*> players;

    void run();
};

#endif /* defined(__Serveur__Server__) */
