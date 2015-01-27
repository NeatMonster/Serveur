#ifndef __Serveur__World__
#define __Serveur__World__

#include "AxisAlignedBB.h"
#include "Entity.h"
#include "Types.h"

#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class Block;
class Chunk;
class EntityPlayer;
class Level;
class Region;

class World {
public:
    World(string_t);

    ~World();

    Level *getLevel();

    string_t getName();

    const std::unordered_set<std::shared_ptr<Entity>> &getEntities();

    void addEntity(std::shared_ptr<Entity>);

    void removeEntity(std::shared_ptr<Entity>);

    const std::unordered_set<std::shared_ptr<EntityPlayer>> &getPlayers();

    void addPlayer(std::shared_ptr<EntityPlayer>);

    void removePlayer(std::shared_ptr<EntityPlayer>);

    std::shared_ptr<Region> getRegion(int_t, int_t);

    std::shared_ptr<Region> loadRegion(int_t, int_t);

    std::shared_ptr<Chunk> getChunk(int_t, int_t);

    std::shared_ptr<Chunk> tryGetChunk(int_t, int_t);

    std::shared_ptr<Chunk> loadChunk(int_t, int_t);

    std::shared_ptr<Chunk> tryLoadChunk(int_t, int_t);

    void unloadChunk(int_t, int_t);

    void tryUnloadChunk(int_t, int_t);

    Block *getBlock(int_t, int_t, int_t);

    bool isFullBlock(int_t, int_t, int_t);

    std::vector<AxisAlignedBB> getCollisions(std::shared_ptr<Entity>, AxisAlignedBB);

    std::vector<AxisAlignedBB> getBlockCollisions(AxisAlignedBB);

    std::vector<std::shared_ptr<Entity>> getEntityCollisions(AxisAlignedBB, std::function<bool(std::shared_ptr<Entity>)>);

    void playSound(double_t, double_t, double_t, string_t, float_t, float_t);

    void onTick();

private:
    Level *level;
    string_t name;
    std::unordered_set<std::shared_ptr<Entity>> entities;
    std::unordered_set<std::shared_ptr<EntityPlayer>> players;
    std::unordered_map<long_t, std::shared_ptr<Chunk>> chunks;
    std::unordered_map<long_t, std::shared_ptr<Region>> regions;

    static inline long_t hash(int_t x, int_t z) {
        return ((long_t) x & 4294967295L) | (((long_t) z & 4294967295L) << 32);
    }
};

#endif /* defined(__Serveur__World__) */
