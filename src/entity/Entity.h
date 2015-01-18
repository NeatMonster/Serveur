#ifndef __Serveur__Entity__
#define __Serveur__Entity__

#include "AxisAlignedBB.h"
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

    AxisAlignedBB getBoundingBox();

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
    AxisAlignedBB boundingBox;

    double_t posX, posY, posZ;
    float_t rotYaw, rotPitch;
    double_t motX, motY, motZ;
    bool onGround;

    int_t lastPosX, lastPosY, lastPosZ;
    int_t lastRotYaw, lastRotPitch;
    int_t lastMotX, lastMotY, lastMotZ;
    bool lastOnGround;

    void setSize(float_t, float_t);

private:
    static int_t nextEntityId;
};

#endif /* defined(__Serveur__Entity__) */
