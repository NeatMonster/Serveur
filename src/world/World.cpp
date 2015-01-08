#include "World.h"

#include "Chunk.h"
#include "EntityPlayer.h"
#include "Level.h"
#include "PacketTimeUpdate.h"
#include "Region.h"
#include "Section.h"

#include <cstring>

World::World(string_t name) : name(name) {
    level = new Level(name);
}

World::~World() {
    delete level;
    for (auto &region : regions)
        delete region.second;
    for (auto &chunk : chunks)
        delete chunk.second;
}

string_t World::getName() {
    return name;
}

Level *World::getLevel() {
    return level;
}

const std::unordered_set<EntityPlayer*> &World::getPlayers() {
    return players;
}

void World::addPlayer(EntityPlayer *player) {
    Position spawn = getLevel()->getSpawn();
    player->setPosition(spawn.x, spawn.y, spawn.z);
    int_t xChunk = (int_t) floor(player->getX()) >> 4;
    int_t zChunk = (int_t) floor(player->getZ()) >> 4;
    players.insert(player);
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++)
            tryLoadChunk(xChunk + x, zChunk + z);
    player->getChunk()->addPlayer(player);
}

void World::removePlayer(EntityPlayer *player) {
    int_t xChunk = (int_t) floor(player->getX()) >> 4;
    int_t zChunk = (int_t) floor(player->getZ()) >> 4;
    player->getChunk()->removePlayer(player);
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++)
            tryUnloadChunk(xChunk + x, zChunk + z);
    players.erase(player);
}

Region *World::getRegion(int_t x, int_t z) {
    auto result = regions.find(hash(x, z));
    if (result == regions.end())
        return loadRegion(x, z);
    return result->second;
}

Region *World::loadRegion(int_t x, int_t z) {
    Region *region = new Region(name, x, z);
    regions[hash(x, z)] = region;
    return region;
}

Chunk *World::getChunk(int_t x, int_t z) {
    auto result = chunks.find(hash(x,z));
    if (result == chunks.end())
        return loadChunk(x, z);
    return result->second;
}

Chunk *World::tryGetChunk(int_t x, int_t z) {
    auto result = chunks.find(hash(x, z));
    if (result == chunks.end())
        return nullptr;
    return result->second;
}

Chunk *World::loadChunk(int_t x, int_t z) {
    Chunk *chunk = new Chunk(this, x, z);
    Region *region = getRegion(floor_d(x / 32.), floor_d(z / 32.));
    if (!region->getChunk(chunk)) {
        Section *section = chunk->sections[0];
        section->blockCount = 1024;
        section->initialize(true);
        for (ubyte_t y = 0; y < 4; y++)
            for (ubyte_t z = 0; z < 16; z++)
                for (ubyte_t x = 0; x < 16; x++) {
                    if (y == 0)
                        section->setBlockType(x + z * 16 + y * 256, 7);
                    else if (y == 1 || y == 2)
                        section->setBlockType(x + z * 16 + y * 256, 3);
                    else if (y == 3) {
                        section->setBlockType(x + z * 16 + y * 256, 2);
                        chunk->heightMap[x + z * 16] = 3;
                    }
                    section->setSkyLight(x + z * 16, 0);
                }
        std::memset(chunk->biomes, 1, 256);
    }
    chunks[hash(x, z)] = chunk;
    return chunk;
}

Chunk *World::tryLoadChunk(int_t x, int_t z) {
    auto result = chunks.find(hash(x, z));
    if (result == chunks.end())
        return loadChunk(x, z);
    return result->second;
}

void World::unloadChunk(int_t x, int_t z) {
    auto result = chunks.find(hash(x, z));
    delete result->second;
    chunks.erase(result);
}

void World::tryUnloadChunk(int_t x, int_t z) {
    if (chunks.find(hash(x, z)) == chunks.end())
        return;
    for (int_t xDist = -VIEW_DISTANCE; xDist <= VIEW_DISTANCE; xDist++)
        for (int_t zDist = -VIEW_DISTANCE; zDist <= VIEW_DISTANCE; zDist++) {
            Chunk *chunk = tryGetChunk(x + xDist, z + zDist);
            if (chunk != nullptr && chunk->getPlayers().size() > 0)
                return;
        }
    unloadChunk(x, z);
}

void World::onTick() {
    for (EntityPlayer *const &player : players)
        player->onTick();
    level->setTime(level->getTime() + 1);
    level->setDayTime(level->getDayTime() + 1);
    if (level->getTime() % 20 == 0)
        for (EntityPlayer *const &player : players)
            player->sendPacket(new PacketTimeUpdate(level->getTime(), level->getDayTime()));
}
