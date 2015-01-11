#ifndef __Serveur__Chunk__
#define __Serveur__Chunk__

#include "Types.h"

#include <unordered_set>

class Entity;
class EntityPlayer;
class Section;
class World;

class Chunk {
    friend class Region;
    friend class World;

public:
    struct Meta {
        int_t x;
        int_t z;
        ushort_t bitmask;
    };

    Chunk(World*, int_t, int_t);

    ~Chunk();

    World *getWorld();

    int_t getX();

    int_t getZ();

    const std::unordered_set<Entity*> &getEntities();

    void addEntity(Entity*);

    void removeEntity(Entity*);

    const std::unordered_set<EntityPlayer*> &getPlayers();

    void addPlayer(EntityPlayer*);

    void removePlayer(EntityPlayer*);

    Meta getMeta();

    void write(ubyte_t*&);

private:
    World *world;
    int_t x;
    int_t z;
    ubyte_t biomes[256];
    int_t heightMap[256];
    Section *sections[16];
    std::unordered_set<Entity*> entities;
    std::unordered_set<EntityPlayer*> players;
};

#endif /* defined(__Serveur__Chunk__) */
