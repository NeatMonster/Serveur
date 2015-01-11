#ifndef __Serveur__World__
#define __Serveur__World__

#include "Types.h"

#include <unordered_set>
#include <unordered_map>

class Chunk;
class Entity;
class EntityPlayer;
class Level;
class Region;

class World {
public:
    World(string_t);

    ~World();

    Level *getLevel();

    string_t getName();

    const std::unordered_set<Entity*> &getEntities();

    void addEntity(Entity*);

    void removeEntity(Entity*);

    const std::unordered_set<EntityPlayer*> &getPlayers();

    void addPlayer(EntityPlayer*);

    void removePlayer(EntityPlayer*);

    Region *getRegion(int_t, int_t);

    Region *loadRegion(int_t, int_t);

    Chunk *getChunk(int_t, int_t);

    Chunk *tryGetChunk(int_t, int_t);

    Chunk *loadChunk(int_t, int_t);

    Chunk *tryLoadChunk(int_t, int_t);

    void unloadChunk(int_t, int_t);

    void tryUnloadChunk(int_t, int_t);

    void onTick();

private:
    Level *level;
    string_t name;
    std::unordered_set<Entity*> entities;
    std::unordered_set<EntityPlayer*> players;
    std::unordered_map<long_t, Chunk*> chunks;
    std::unordered_map<long_t, Region*> regions;

    static inline long_t hash(int_t x, int_t z) {
        return ((long_t) x & 4294967295L) | (((long_t) z & 4294967295L) << 32);
    }
};

#endif /* defined(__Serveur__World__) */
