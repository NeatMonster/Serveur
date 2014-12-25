#ifndef __Serveur__Player__
#define __Serveur__Player__

#include "ChatMessage.h"
#include "CommandSender.h"
#include "LivingEntity.h"
#include "InventoryPlayer.h"

class PlayerConnection;
class ServerPacket;

class Player : public LivingEntity, public CommandSender {
public:
    Player(World*, PlayerConnection*);

    virtual ~Player();

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
    InventoryPlayer inventory;
    PlayerConnection *connect;
    string_t uuid;
    string_t name;
};

#endif /* defined(__Serveur__Player__) */
