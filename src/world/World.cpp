#include "World.h"

#include "Chunk.h"
#include "Level.h"
#include "PacketTimeUpdate.h"
#include "Player.h"
#include "Section.h"

#include <cstring>

World::World(string_t name) : name(name) {
    level = new Level(name);
}

World::~World() {
    delete level;
    for (auto &chunk : chunks)
        delete chunk.second;
}

string_t World::getName() {
    return name;
}

Level *World::getLevel() {
    return level;
}

std::set<Player*> World::getPlayers() {
    return players;
}

void World::addPlayer(Player *player) {
    players.insert(player);
    Chunk *chunk = player->getChunk();
    chunk->addPlayer(player);
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++)
            tryLoadChunk(std::make_pair(chunk->getX() + x, chunk->getZ() + z));
    player->onJoinWorld();
}

void World::removePlayer(Player *player) {
    player->onQuitWorld();
    Chunk *chunk = player->getChunk();
    chunk->removePlayer(player);
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++)
            tryUnloadChunk(std::make_pair(chunk->getX() + x, chunk->getZ() + z));
    players.erase(player);
}

Chunk *World::getChunk(chunk_t c) {
    auto result = chunks.find(c);
    if (result == chunks.end())
        return loadChunk(c);
    return result->second;
}

Chunk *World::tryGetChunk(chunk_t c) {
    auto result = chunks.find(c);
    if (result == chunks.end())
        return nullptr;
    return result->second;
}

Chunk *World::loadChunk(chunk_t c) {
    Chunk *chunk = new Chunk(this, c.first, c.second);
    Section *section = chunk->sections[0];
    section->initialize(true);
    for (ubyte_t y = 0; y < 4; y++)
        for (ubyte_t z = 0; z < 16; z++)
            for (ubyte_t x = 0; x < 16; x++) {
                if (y == 0)
                    section->setBlockData(x + z * 16 + y * 256, 7);
                else if (y == 1 || y == 2)
                    section->setBlockData(x + z * 16 + y * 256, 3);
                else {
                    section->setBlockData(x + z * 16 + y * 256, 2);
                    chunk->heightMap[x + z * 16] = y;
                }
                section->setBlockLight(x + z * 16, 0);
            }
    chunks[c] = chunk;
    return chunk;
}

Chunk *World::tryLoadChunk(chunk_t c) {
    auto result = chunks.find(c);
    if (result == chunks.end())
        return loadChunk(c);
    return result->second;
}

void World::unloadChunk(chunk_t c) {
    Chunk *chunk = chunks[c];
    chunks.erase(c);
    delete chunk;
}

void World::tryUnloadChunk(chunk_t c) {
    if (chunks.find(c) == chunks.end())
        return;
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++) {
            Chunk *chunk = tryGetChunk(std::make_pair(c.first + x, c.second + z));
            if (chunk != nullptr && chunk->getPlayers().size() > 0)
                return;
        }
    unloadChunk(c);
}

void World::onTick() {
    for (Player *const &player : players)
        player->onTick();
    level->setTime(level->getTime());
    level->setDayTime(level->getDayTime() + 1);
    if (level->getTime() % 20 == 0)
        for (Player *const &player : players)
            player->sendPacket(new PacketTimeUpdate(level->getTime(), level->getDayTime()));
}
