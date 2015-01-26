#include "Chunk.h"

#include "Block.h"
#include "Section.h"

#include <cstring>

Chunk::Chunk(World *world, int_t x, int_t z) : world(world), x(x), z(z) {
    std::memset(biomes, 255, 256);
    std::memset(heightMap, 0, 1024);
    for (int_t y = 0; y < 16; y++)
        sections[y] = new Section(y);
}

Chunk::~Chunk() {
    for (int_t y = 0; y < 16; y++)
        delete sections[y];
}

World *Chunk::getWorld() {
    return world;
}

int_t Chunk::getX() {
    return x;
}

int_t Chunk::getZ() {
    return z;
}

const std::unordered_set<std::shared_ptr<Entity>> &Chunk::getEntities() {
    return entities;
}

void Chunk::addEntity(std::shared_ptr<Entity> entity) {
    entities.insert(entity);
}

void Chunk::removeEntity(std::shared_ptr<Entity> entity) {
    entities.erase(entity);
}

const std::unordered_set<std::shared_ptr<EntityPlayer>> &Chunk::getPlayers() {
    return players;
}

void Chunk::addPlayer(std::shared_ptr<EntityPlayer> player) {
    players.insert(player);
}

void Chunk::removePlayer(std::shared_ptr<EntityPlayer> player) {
    players.erase(player);
}

Block *Chunk::getBlock(int_t x, int_t y, int_t z) {
    return Block::getBlock(sections[y / 16]->getBlockType(x + z * 16 + (y % 16) * 256));
}

Chunk::Meta Chunk::getMeta() {
    ushort bitmask = 0;
    for (int y = 0; y < 16; y++)
        if (sections[y]->blockCount > 0)
            bitmask |= 1 << y;
    return {x, z, bitmask};
}

void Chunk::write(ubyte_t *&data) {
    for (Section *&section : sections)
        if (section->blockCount > 0) {
            std::memcpy(data, section->blockData, 8192);
            data += 8192;
        }
    for (Section *&section : sections)
        if (section->blockCount > 0) {
            std::memcpy(data, section->blockLight, 2048);
            data += 2048;
        }
    for (Section *&section : sections)
        if (section->blockCount > 0) {
            std::memcpy(data, section->skyLight, 2048);
            data += 2048;
        }
    for (int i = 0; i < 256; i++)
        *(data++) = biomes[i];
}
