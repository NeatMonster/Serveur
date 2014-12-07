#ifndef __Serveur__Entity__
#define __Serveur__Entity__

#include "Types.h"

#include <set>

class Chunk;
class Player;
class World;

class Entity {
public:
    enum Type { PLAYER };

    Entity(World*);

    virtual ~Entity();

    virtual Type getType() = 0;

    int_t getEntityId();

    Chunk *getChunk();

    virtual World *getWorld();

    std::set<Player*> getWatchers();

    double_t getX();

    double_t getY();

    double_t getZ();

    virtual void setPosition(double_t, double_t, double_t);

    virtual void setRotation(float_t, float_t);

    bool isDead();

    void setDead();

    virtual void onTick();

protected:
    Type type;
    int_t entityId;
    int_t ticks;
    bool dead;

    World * world;
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
