#ifndef __Serveur__Entity__
#define __Serveur__Entity__

#include "Types.h"

#include <unordered_set>

class Chunk;
class EntityPlayer;
class ServerPacket;
class World;

class Entity {
    friend class PacketHandler;

public:
    enum Type { PLAYER, ITEM = 2 };

    Entity(World*);

    virtual ~Entity();

    virtual Type getType() = 0;

    varint_t getEntityId();

    bool isDead();

    void setDead();

    World *getWorld();

    double_t getX();

    double_t getY();

    double_t getZ();

    float_t getYaw();

    float_t getPitch();

    void setPosition(double_t, double_t, double_t);

    virtual void move(double_t, double_t, double_t);

    void setRotation(float_t, float_t);

    virtual void rotate(float_t, float_t);

    Chunk *getChunk();

    std::unordered_set<EntityPlayer*> getWatchers();

    virtual ServerPacket *getSpawnPacket() = 0;

    virtual ServerPacket *getMetadataPacket() = 0;

    virtual void onTick();

protected:
    Type type;
    World *world;
    varint_t entityId;
    int_t ticks;
    bool dead;

    double_t x, y, z;
    float_t yaw, pitch;
    bool onGround;
    int_t lastX, lastY, lastZ;
    int_t lastYaw, lastPitch;
    bool lastOnGround;

private:
    static int_t nextEntityId;
};

#endif /* defined(__Serveur__Entity__) */
