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

    virtual ~EntityPlayer();

    virtual Type getType();

    World *getWorld();

    virtual void move(double_t, double_t, double_t);

    string_t getUUID();

    string_t getName();

    string_t getIP();

    ushort_t getPort();

    float_t getPing();

    InventoryPlayer &getInventory();

    void sendMessage(ChatMessage&);

    void disconnect(string_t);

    void sendPacket(ServerPacket*);

    void onJoinGame();

    void onQuitGame();

    virtual void onTick();

private:
    PlayerConnection *connect;
    InventoryPlayer inventory;
    string_t uuid;
    string_t name;
};

#endif /* defined(__Serveur__EntityPlayer__) */
