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
    enum GameMode { SURVIVAL, CREATIVE, ADVENTURE, SPECTATOR };

    EntityPlayer(World*, PlayerConnection*);

    Type getType() { return PLAYER; }

    int_t getTrackingRange() { return 512; }

    int_t getUpdateFrequency() { return 2; }

    bool sendVelocityUpdates() { return false; }

    World *getWorld();

    string_t getUUID();

    string_t getName();

    PlayerConnection *getConnection();

    InventoryPlayer &getInventory();

    GameMode getGameMode();

    void setGameMode(GameMode);

    void drop(std::shared_ptr<ItemStack>);

    void disconnect(string_t);

    void sendMessage(ChatMessage&);

    void sendPacket(std::shared_ptr<ServerPacket>);

    void onJoinGame();

    void onQuitGame();

    std::shared_ptr<ServerPacket> getSpawnPacket();

    void onChunk(Chunk*, Chunk*);

    void onTick();

private:
    PlayerConnection *connect;
    InventoryPlayer inventory;
    string_t uuid;
    string_t name;
    GameMode gameMode;
};

#endif /* defined(__Serveur__EntityPlayer__) */
