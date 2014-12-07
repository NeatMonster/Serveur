#ifndef __Serveur__Entity__
#define __Serveur__Entity__

#include "Types.h"

class Chunk;
class World;

class Entity {
public:
    enum Type { PLAYER };

    Entity(World*);

    virtual ~Entity();

    virtual void getType() = 0;

    int_t getEntityId();

    virtual World *getWorld();

    Chunk *getChunk();

    void move(double_t, double_t, double_t);

    void rotate(float_t, float_t);

    bool isDead();

    void setDead();

    virtual void onTick();

protected:
    Type type;
    int_t entityId;
    int_t ticks;
    bool dead;

    World * world;
    int_t x, y, z;
    int_t yaw, pitch;
    bool onGround;
    int_t lastX, lastY, lastZ;
    int_t lastYaw, lastPitch;
    bool lastOnGround;

private:
    static int_t nextEntityId;
};

#endif /* defined(__Serveur__Entity__) */
