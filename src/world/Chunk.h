#ifndef __Serveur__Chunk__
#define __Serveur__Chunk__

#include "Types.h"

#include <set>

class Entity;
class Player;
class Section;
class World;

class Chunk {
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

    std::set<Entity*> getEntities();

    void addEntity(Entity*);

    void removeEntity(Entity*);

    std::set<Player*> getPlayers();

    void addPlayer(Player*);

    void removePlayer(Player*);

    Meta getMeta();

    void write(ubyte_t*&);

private:
    World *world;
    int_t x;
    int_t z;
    ubyte_t biomes[256];
    int_t heightMap[256];
    Section *sections[16];
    std::set<Entity*> entities;
    std::set<Player*> players;
};

#endif /* defined(__Serveur__Chunk__) */
