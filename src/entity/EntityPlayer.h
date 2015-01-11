#ifndef __Serveur__EntityPlayer__
#define __Serveur__EntityPlayer__

#include "ChatMessage.h"
#include "CommandSender.h"
#include "EntityLiving.h"
#include "InventoryPlayer.h"

class PlayerConnection;
class ServerPacket;

class EntityPlayer : public EntityLiving, public CommandSender {
public:
    EntityPlayer(World*, PlayerConnection*);

    Type getType();

    World *getWorld();

    void move(double_t, double_t, double_t);

    string_t getUUID();

    string_t getName();

    PlayerConnection *getConnection();

    InventoryPlayer &getInventory();

    void disconnect(string_t);

    void sendMessage(ChatMessage&);

    void sendPacket(ServerPacket*);

    void onJoinGame();

    void onQuitGame();

    ServerPacket *getSpawnPacket();

private:
    PlayerConnection *connect;
    InventoryPlayer inventory;
    string_t uuid;
    string_t name;
};

#endif /* defined(__Serveur__EntityPlayer__) */
