#include "World.h"

#include "Block.h"
#include "Chunk.h"
#include "EntityPlayer.h"
#include "Level.h"
#include "MathUtils.h"
#include "PacketDestroyEntities.h"
#include "PacketEntityMetadata.h"
#include "PacketTimeUpdate.h"
#include "Region.h"
#include "Section.h"

#include <cstring>

World::World(string_t name) : name(name) {
    level = new Level(name);
}

World::~World() {
    delete level;
}

string_t World::getName() {
    return name;
}

Level *World::getLevel() {
    return level;
}

const std::unordered_set<std::shared_ptr<Entity>> &World::getEntities() {
    return entities;
}

void World::addEntity(std::shared_ptr<Entity> entity) {
    entities.insert(entity);
    entity->getChunk()->addEntity(entity);
    std::shared_ptr<EntityPlayer> player = std::dynamic_pointer_cast<EntityPlayer>(entity);
    if (player)
        addPlayer(player);
    std::shared_ptr<ServerPacket> spawnPacket = entity->getSpawnPacket();
    std::unordered_set<std::shared_ptr<EntityPlayer>> watchers = entity->getWatchers();
    for (std::shared_ptr<EntityPlayer> watcher : watchers)
        watcher->sendPacket(spawnPacket);
    if (entity->getDataWatcher().hasChanged()) {
        std::shared_ptr<PacketEntityMetadata> metaPacket =
            std::make_shared<PacketEntityMetadata>(entity->getEntityId(), &entity->getDataWatcher());
        for (std::shared_ptr<EntityPlayer> watcher : watchers)
            watcher->sendPacket(metaPacket);
    }
}

void World::removeEntity(std::shared_ptr<Entity> entity) {
    std::shared_ptr<PacketDestroyEntities> packet = std::make_shared<PacketDestroyEntities>(entity->getEntityId());
    for (std::shared_ptr<EntityPlayer> watcher : entity->getWatchers())
        watcher->sendPacket(packet);
    std::shared_ptr<EntityPlayer> player = std::dynamic_pointer_cast<EntityPlayer>(entity);
    if (player)
        removePlayer(player);
    entity->getChunk()->removeEntity(entity);
    entities.erase(entity);
}

const std::unordered_set<std::shared_ptr<EntityPlayer>> &World::getPlayers() {
    return players;
}

void World::addPlayer(std::shared_ptr<EntityPlayer> player) {
    int_t xChunk = (int_t) floor(player->getX()) >> 4;
    int_t zChunk = (int_t) floor(player->getZ()) >> 4;
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++)
            tryLoadChunk(xChunk + x, zChunk + z);
    players.insert(player);
    player->getChunk()->addPlayer(player);
    player->onJoinGame();
}

void World::removePlayer(std::shared_ptr<EntityPlayer> player) {
    player->onQuitGame();
    player->getChunk()->removePlayer(player);
    players.erase(player);
    int_t xChunk = (int_t) floor(player->getX()) >> 4;
    int_t zChunk = (int_t) floor(player->getZ()) >> 4;
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++)
            tryUnloadChunk(xChunk + x, zChunk + z);
}

std::shared_ptr<Region> World::getRegion(int_t x, int_t z) {
    auto result = regions.find(hash(x, z));
    if (result == regions.end())
        return loadRegion(x, z);
    return result->second;
}

std::shared_ptr<Region> World::loadRegion(int_t x, int_t z) {
    std::shared_ptr<Region> region = std::make_shared<Region>(name, x, z);
    regions[hash(x, z)] = region;
    return region;
}

std::shared_ptr<Chunk> World::getChunk(int_t x, int_t z) {
    auto result = chunks.find(hash(x,z));
    if (result == chunks.end())
        return loadChunk(x, z);
    return result->second;
}

std::shared_ptr<Chunk> World::tryGetChunk(int_t x, int_t z) {
    auto result = chunks.find(hash(x, z));
    if (result == chunks.end())
        return nullptr;
    return result->second;
}

std::shared_ptr<Chunk> World::loadChunk(int_t x, int_t z) {
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(this, x, z);
    std::shared_ptr<Region> region = getRegion(MathUtils::floor_d(x / 32.), MathUtils::floor_d(z / 32.));
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

std::shared_ptr<Chunk> World::tryLoadChunk(int_t x, int_t z) {
    auto result = chunks.find(hash(x, z));
    if (result == chunks.end())
        return loadChunk(x, z);
    return result->second;
}

void World::unloadChunk(int_t x, int_t z) {
    auto result = chunks.find(hash(x, z));
    chunks.erase(result);
}

void World::tryUnloadChunk(int_t x, int_t z) {
    if (chunks.find(hash(x, z)) == chunks.end())
        return;
    for (int_t xDist = -VIEW_DISTANCE; xDist <= VIEW_DISTANCE; xDist++)
        for (int_t zDist = -VIEW_DISTANCE; zDist <= VIEW_DISTANCE; zDist++) {
            std::shared_ptr<Chunk> chunk = tryGetChunk(x + xDist, z + zDist);
            if (chunk != nullptr && chunk->getPlayers().size() > 0)
                return;
        }
    unloadChunk(x, z);
}

Block *World::getBlock(int_t x, int_t y, int_t z) {
    return getChunk((int_t) MathUtils::floor_d(x) >> 4, (int_t) MathUtils::floor_d(z) >> 4)->getBlock(x % 16, y, z % 16);
}

bool World::isFullBlock(int_t x, int_t y, int_t z) {
    AxisAlignedBB boundingBox = getBlock(x, y, z)->getBoundingBox().offset(x, y, z);
    return boundingBox.maxX - boundingBox.minX
         + boundingBox.maxY - boundingBox.minY
         + boundingBox.maxZ - boundingBox.minZ >= 3.;
}

std::vector<AxisAlignedBB> World::getCollisions(std::shared_ptr<Entity> entity, AxisAlignedBB boundingBox) {
    std::vector<AxisAlignedBB> collisions = getBlockCollisions(boundingBox);
    for (std::shared_ptr<Entity> otherEntity : entities)
        if (otherEntity != entity) {
            AxisAlignedBB otherBoundingBox = otherEntity->getBoundingBox();
            if (otherBoundingBox.intersects(boundingBox))
                collisions.push_back(otherBoundingBox);
        }
    return collisions;
}

std::vector<AxisAlignedBB> World::getBlockCollisions(AxisAlignedBB boundingBox) {
    std::vector<AxisAlignedBB> collisions;
    for (int_t x = MathUtils::floor_d(boundingBox.minX); x < MathUtils::floor_d(boundingBox.maxX + 1); x++)
        for (int_t y = MathUtils::floor_d(boundingBox.minY); y < MathUtils::floor_d(boundingBox.maxY + 1); y++)
            for (int_t z = MathUtils::floor_d(boundingBox.minZ); z < MathUtils::floor_d(boundingBox.maxZ + 1); z++) {
                AxisAlignedBB otherBoundingBox = getBlock(x, y, z)->getBoundingBox().offset(x, y, z);
                if (otherBoundingBox.intersects(boundingBox))
                    collisions.push_back(otherBoundingBox);
            }
    return collisions;
}

std::vector<std::shared_ptr<Entity>> World::getEntityCollisions(AxisAlignedBB boundingBox, std::function<bool(std::shared_ptr<Entity>)> predicate) {
    std::vector<std::shared_ptr<Entity>> entities;
    for (std::shared_ptr<Entity> otherEntity : this->entities)
        if (predicate(otherEntity)) {
            AxisAlignedBB otherBoundingBox = otherEntity->getBoundingBox();
            if (otherBoundingBox.intersects(boundingBox))
                entities.push_back(otherEntity);
        }
    return entities;
}

void World::onTick() {
    for (std::shared_ptr<Entity> entity : std::unordered_set<std::shared_ptr<Entity>>(entities)) {
        entity->onTick();
        if (entity->isDead())
            removeEntity(entity);
    }
    level->setTime(level->getTime() + 1);
    level->setDayTime(level->getDayTime() + 1);
    if (level->getTime() % 20 == 0) {
        std::shared_ptr<PacketTimeUpdate> packet = std::make_shared<PacketTimeUpdate>(level->getTime(), level->getDayTime());
        for (std::shared_ptr<EntityPlayer> player : players)
            player->sendPacket(packet);
    }
}
