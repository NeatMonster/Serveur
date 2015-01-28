#ifndef __Serveur__Server__
#define __Serveur__Server__

#include "ChatMessage.h"
#include "CommandManager.h"
#include "CommandSender.h"
#include "Database.h"
#include "NetworkManager.h"
#include "Types.h"

#include <unordered_set>
#include <set>

class Player;
class World;

class Server : public CommandSender {
public:
    static Server *getServer();

    static void broadcast(ChatMessage&);

    static CommandManager *getCommands();

    static Database *getDatabase();

    static NetworkManager *getNetwork();

    static EntityPlayer *getPlayer(string_t);

    static std::set<EntityPlayer*> getPlayers();

    Server(ushort_t);

    virtual ~Server();

    void stop();

    string_t getName();

    World *getWorld();

    void sendMessage(ChatMessage&);

private:
    static Server *instance;
    CommandManager *commands;
    Database *database;
    NetworkManager *network;
    bool running;
    long_t ticks;
    World *world;

    void run();
};

#endif /* defined(__Serveur__Server__) */
