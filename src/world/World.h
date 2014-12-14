#ifndef __Serveur__World__
#define __Serveur__World__

#include "Types.h"

#include <set>
#include <map>

class Chunk;
class Entity;
class Level;
class Player;
class Region;

class World {
public:
    World(string_t);

    ~World();

    Level *getLevel();

    string_t getName();

    std::set<Player*> getPlayers();

    void addPlayer(Player*);

    void removePlayer(Player*);

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
    std::set<Player*> players;
    std::map<long_t, Chunk*> chunks;
    std::map<long_t, Region*> regions;

    static inline long_t hash(int_t x, int_t z) {
        return ((long_t) x & 4294967295L) | (((long_t) z & 4294967295L) << 32);
    }
};

#endif /* defined(__Serveur__World__) */
