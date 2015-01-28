#include "World.h"

#include "Block.h"
#include "Chunk.h"
#include "EntityPlayer.h"
#include "Level.h"
#include "MathUtils.h"
#include "PacketDestroyEntities.h"
#include "PacketEntityMetadata.h"
#include "PacketSoundEffect.h"
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

std::set<Entity*> World::getEntities() {
    std::set<Entity*> entities;
    for (auto entity : this->entities)
        entities.insert(entity.second.get());
    return entities;
}

void World::addEntity(varint_t entityId, std::shared_ptr<Entity> entity) {
    entities[entityId] = entity;
    entity->getChunk()->addEntity(entity.get());
    std::shared_ptr<EntityPlayer> player = std::dynamic_pointer_cast<EntityPlayer>(entity);
    if (player)
        addPlayer(entityId, player);
    std::shared_ptr<ServerPacket> spawnPacket = entity->getSpawnPacket();
    std::set<EntityPlayer*> watchers = entity->getWatchers();
    for (EntityPlayer *watcher : watchers)
        watcher->sendPacket(spawnPacket);
    if (entity->getDataWatcher().hasChanged()) {
        std::shared_ptr<PacketEntityMetadata> metaPacket =
            std::make_shared<PacketEntityMetadata>(entity->getEntityId(), &entity->getDataWatcher());
        for (EntityPlayer *watcher : watchers)
            watcher->sendPacket(metaPacket);
    }
}

std::shared_ptr<Entity> World::removeEntity(varint_t entityId) {
    std::shared_ptr<Entity> entity = entities[entityId];
    std::shared_ptr<PacketDestroyEntities> packet = std::make_shared<PacketDestroyEntities>(entityId);
    for (EntityPlayer *watcher: entity->getWatchers())
        watcher->sendPacket(packet);
    std::shared_ptr<EntityPlayer> player = std::dynamic_pointer_cast<EntityPlayer>(entity);
    if (player)
        removePlayer(entityId);
    entity->getChunk()->removeEntity(entity.get());
    entities.erase(entities.find(entityId));
    return entity;
}

std::set<EntityPlayer*> World::getPlayers() {
    std::set<EntityPlayer*> players;
    for (auto player : this->players)
        players.insert(player.second.get());
    return players;
}

void World::addPlayer(varint_t entityId, std::shared_ptr<EntityPlayer> player) {
    players[entityId] = player;
    player->getChunk()->addPlayer(player.get());
    player->onJoinGame();
}

std::shared_ptr<EntityPlayer> World::removePlayer(varint_t entityId) {
    std::shared_ptr<EntityPlayer> player = players[entityId];
    player->onQuitGame();
    player->getChunk()->removePlayer(player.get());
    players.erase(players.find(entityId));
    int_t xChunk = (int_t) floor(player->getX()) >> 4;
    int_t zChunk = (int_t) floor(player->getZ()) >> 4;
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++)
            tryUnloadChunk(xChunk + x, zChunk + z);
    return player;
}

Region *World::getRegion(int_t x, int_t z) {
    auto result = regions.find(hash(x, z));
    if (result == regions.end())
        return loadRegion(x, z);
    return result->second.get();
}

Region *World::loadRegion(int_t x, int_t z) {
    Region *region = new Region(name, x, z);
    regions[hash(x, z)] = std::shared_ptr<Region>(region);
    return region;
}

Chunk *World::getChunk(int_t x, int_t z) {
    auto result = chunks.find(hash(x,z));
    if (result == chunks.end())
        return loadChunk(x, z);
    return result->second.get();
}

Chunk *World::tryGetChunk(int_t x, int_t z) {
    auto result = chunks.find(hash(x, z));
    if (result == chunks.end())
        return nullptr;
    return result->second.get();
}

Chunk *World::loadChunk(int_t x, int_t z) {
    Chunk *chunk = new Chunk(this, x, z);
    Region *region = getRegion(MathUtils::floor_d(x / 32.), MathUtils::floor_d(z / 32.));
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
    chunks[hash(x, z)] = std::shared_ptr<Chunk>(chunk);
    return chunk;
}

Chunk *World::tryLoadChunk(int_t x, int_t z) {
    auto result = chunks.find(hash(x, z));
    if (result == chunks.end())
        return loadChunk(x, z);
    return result->second.get();
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
            Chunk *chunk = tryGetChunk(x + xDist, z + zDist);
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

std::vector<AxisAlignedBB> World::getCollisions(Entity *entity, AxisAlignedBB boundingBox) {
    std::vector<AxisAlignedBB> collisions = getBlockCollisions(boundingBox);
    for (Entity *otherEntity : getEntities())
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

std::vector<Entity*> World::getEntityCollisions(AxisAlignedBB boundingBox, std::function<bool(Entity*)> predicate) {
    std::vector<Entity*> entities;
    for (Entity *otherEntity : getEntities())
        if (predicate(otherEntity)) {
            AxisAlignedBB otherBoundingBox = otherEntity->getBoundingBox();
            if (otherBoundingBox.intersects(boundingBox))
                entities.push_back(otherEntity);
        }
    return entities;
}

void World::playSound(double_t x, double_t y, double_t z, string_t sound, float_t volume, float_t pitch) {
    std::shared_ptr<PacketSoundEffect> packet = std::make_shared<PacketSoundEffect>();
    packet->soundName = sound;
    packet->positionX = (int_t) (x * 8.);
    packet->positionY = (int_t) (y * 8.);
    packet->positionZ = (int_t) (z * 8.);
    packet->volume = volume;
    packet->pitch = (ubyte_t) (pitch * 63.);
    double_t radius = MathUtils::min(volume * 16., 16.);
    for (EntityPlayer *player : getPlayers()) {
        double_t deltaX = player->getX() - x;
        double_t deltaY = player->getY() - y;
        double_t deltaZ = player->getZ() - z;
        double_t delta = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;
        if (delta <= radius * radius)
            player->sendPacket(packet);
    }
}

void World::onTick() {
    for (Entity *entity : getEntities()) {
        entity->onTick();
        if (entity->isDead())
            removeEntity(entity->getEntityId());
    }
    level->setTime(level->getTime() + 1);
    level->setDayTime(level->getDayTime() + 1);
    if (level->getTime() % 20 == 0) {
        std::shared_ptr<PacketTimeUpdate> packet = std::make_shared<PacketTimeUpdate>(level->getTime(), level->getDayTime());
        for (EntityPlayer *player : getPlayers())
            player->sendPacket(packet);
    }
}
