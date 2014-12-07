#ifndef __Serveur__World__
#define __Serveur__World__

#include "Types.h"

#include <set>
#include <map>

class Chunk;
class Entity;
class Level;
class Player;

class World {
public:
    typedef std::pair<int_t, int_t> chunk_t;

    World(string_t);

    ~World();

    Level *getLevel();

    string_t getName();

    std::set<Player*> getPlayers();

    void addPlayer(Player*);

    void removePlayer(Player*);

    Chunk *getChunk(chunk_t);

    Chunk *tryGetChunk(chunk_t);

    Chunk *loadChunk(chunk_t);

    Chunk *tryLoadChunk(chunk_t);

    void unloadChunk(chunk_t);

    void tryUnloadChunk(chunk_t);

    void onTick();

private:
    Level *level;
    string_t name;
    std::set<Player*> players;
    std::map<chunk_t, Chunk*> chunks;
};

#endif /* defined(__Serveur__World__) */
