#include "Entity.h"

#include "Chunk.h"
#include "EntityPlayer.h"
#include "MathUtils.h"
#include "PacketEntityLook.h"
#include "PacketEntityMetadata.h"
#include "PacketEntityMove.h"
#include "PacketEntityMoveLook.h"
#include "PacketEntityTeleport.h"
#include "PacketEntityVelocity.h"
#include "World.h"

Entity::Entity(World *world) : world(world), ticks(0), dead(false), boundingBox({0, 0, 0, 0, 0, 0}), width(0), height(0),
    posX(0), posY(0), posZ(0), rotYaw(0), rotPitch(0), motX(0), motY(0), motZ(0), onGround(false), noClip(false),
    lastPosX(0), lastPosY(0), lastPosZ(0), lastRotYaw(0), lastRotPitch(0), lastMotX(0), lastMotY(0), lastMotZ(0), lastOnGround(false) {
    entityId = nextEntityId++;
}

Entity::~Entity() {}

varint_t Entity::getEntityId() {
    return entityId;
}

bool Entity::isDead() {
    return dead;
}

void Entity::setDead() {
    dead = true;
}

World *Entity::getWorld() {
    return world;
}

Chunk *Entity::getChunk() {
    return world->getChunk((int_t) MathUtils::floor_d(posX) >> 4, (int_t) MathUtils::floor_d(posZ) >> 4);
}

double_t Entity::getX() {
    return posX;
}

double_t Entity::getY() {
    return posY;
}

double_t Entity::getZ() {
    return posZ;
}

float_t Entity::getYaw() {
    return rotYaw;
}

float_t Entity::getPitch() {
    return rotPitch;
}

double_t Entity::getVelocityX() {
    return motX;
}

double_t Entity::getVelocityY() {
    return motY;
}

double_t Entity::getVelocityZ() {
    return motZ;
}

AxisAlignedBB Entity::getBoundingBox() {
    return boundingBox;
}

DataWatcher &Entity::getDataWatcher() {
    return dataWatcher;
}

bool Entity::getFlag(int flag) {
    return (getDataWatcher().getByte(0) & 1 << flag) != 0;
}

bool Entity::isBurning() {
    return getFlag(0); // TODO Finir la méthode, voire celle du NMS
}

bool Entity::isSneaking() {
    return getFlag(1);
}

bool Entity::isSprinting() {
    return getFlag(3);
}

bool Entity::isInvisible() {
    return getFlag(5);
}

double_t Entity::getDistance(Entity *entity) {
    return (posX - entity->getX()) * (posX - entity->getX())
         + (posY - entity->getY()) * (posY - entity->getY())
         + (posZ - entity->getZ()) * (posZ - entity->getZ());
}

void Entity::move(double_t x, double_t y, double_t z) {
    int_t oldChunkX = (int_t) floor(posX) >> 4;
    int_t oldChunkZ = (int_t) floor(posZ) >> 4;
    if (noClip) {
        boundingBox.offset(x, y, z);
        setPosition();
    } else {
        double_t savX = x, savY = y, savZ = z;
        std::vector<AxisAlignedBB> collisions = world->getCollisions(this, boundingBox.clone().add(x, y, z));
        for (AxisAlignedBB &collision : collisions) {
            x = collision.calculateXOffset(boundingBox, x);
            y = collision.calculateYOffset(boundingBox, y);
            z = collision.calculateZOffset(boundingBox, z);
        }
        boundingBox.offset(x, y, z);
        setPosition();
        onGround = y != savY && savY < 0;
        if (x != savX)
            motX = 0;
        if (y != savY)
            motY = 0;
        if (z != savZ)
            motZ = 0;
    }
    int_t newChunkX = (int_t) floor(posX) >> 4;
    int_t newChunkZ = (int_t) floor(posZ) >> 4;
    if (oldChunkX != newChunkX || oldChunkZ != newChunkZ)
        onChunk(world->getChunk(oldChunkX, oldChunkZ), world->getChunk(newChunkZ, newChunkZ));
}

void Entity::setPosition(double_t x, double_t y, double_t z) {
    int_t oldChunkX = (int_t) floor(posX) >> 4;
    int_t oldChunkZ = (int_t) floor(posZ) >> 4;
    posX = x;
    posY = y;
    posZ = z;
    boundingBox = {x - width / 2., y, z - width / 2., x + width / 2., y + height, z + width / 2.};
    int_t newChunkX = (int_t) floor(posX) >> 4;
    int_t newChunkZ = (int_t) floor(posZ) >> 4;
    if (oldChunkX != newChunkX || oldChunkZ != newChunkZ)
        onChunk(world->getChunk(oldChunkX, oldChunkZ), world->getChunk(newChunkZ, newChunkZ));
}

void Entity::setRotation(float_t yaw, float_t pitch) {
    rotYaw = MathUtils::mod<float_t>(yaw, 360.);
    rotPitch = MathUtils::mod<float_t>(pitch, 360.);
}

void Entity::setVelocity(double_t motX, double_t motY, double_t motZ) {
    this->motX = motX;
    this->motY = motY;
    this->motZ = motZ;
}

bool Entity::pushOutOfBlocks(double_t x, double_t y, double_t z) {
    double_t blockX = MathUtils::floor_d(x);
    double_t blockY = MathUtils::floor_d(y);
    double_t blockZ = MathUtils::floor_d(z);
    if (world->getBlockCollisions(boundingBox).empty() && !world->isFullBlock(blockX, blockY, blockZ))
        return false;
    byte_t direction = 3;
    double_t distance = 9999;
    double_t deltaX = x - blockX;
    double_t deltaY = y - blockY;
    double_t deltaZ = z - blockZ;
    if (!world->isFullBlock(blockX - 1, blockY, blockZ) && deltaX < distance) {
        distance = deltaX;
        direction = 0;
    }
    if (!world->isFullBlock(blockX + 1, blockY, blockZ) && 1 - deltaX < distance) {
        distance = 1 - deltaX;
        direction = 1;
    }
    if (!world->isFullBlock(blockX, blockY + 1, blockZ) && 1 - deltaY < distance) {
        distance = 1 - deltaY;
        direction = 3;
    }
    if (!world->isFullBlock(blockX, blockY, blockZ - 1) && deltaZ < distance) {
        distance = deltaZ;
        direction = 4;
    }
    if (!world->isFullBlock(blockX, blockY, blockZ + 1) && 1 - deltaZ < distance) {
        distance = 1 - deltaZ;
        direction = 5;
    }
    float_t speed = MathUtils::random_f() * 0.2 + 0.1;
    if (direction == 0)
        motX = -speed;
    if (direction == 1)
        motX = speed;
    if (direction == 3)
        motY = speed;
    if (direction == 4)
        motZ = -speed;
    if (direction == 5)
        motZ = speed;
    return true;
}

std::set<EntityPlayer*> Entity::getWatchers() {
    std::set<EntityPlayer*> watchers;
    int_t xChunk = (int_t) floor(posX) >> 4;
    int_t zChunk = (int_t) floor(posZ) >> 4;
    int viewDistance = MathUtils::min(VIEW_DISTANCE, 1 + getTrackingRange() / 16);
    for (int x = -viewDistance; x <= viewDistance; ++x)
        for (int z = -viewDistance; z <= viewDistance; ++z) {
            Chunk *chunk = world->tryGetChunk(xChunk + x, zChunk + z);
            if (chunk != nullptr)
                for (EntityPlayer *watcher : chunk->getPlayers())
                    if (watcher->getEntityId() != getEntityId() && getDistance(watcher) < getTrackingRange() * getTrackingRange())
                        watchers.insert(watcher);
        }
    return watchers;
}

void Entity::onChunk(Chunk *oldChunk, Chunk *newChunk) {
    oldChunk->removeEntity(this);
    newChunk->addEntity(this);
}

void Entity::onCollision(EntityPlayer*) {}

void Entity::onTick() {
    if (ticks++ % getUpdateFrequency() > 0)
        return;
    std::set<EntityPlayer*> watchers = getWatchers();
    int_t posX = (int_t) MathUtils::floor_d(this->posX * 32.);
    int_t posY = (int_t) MathUtils::floor_d(this->posY * 32.);
    int_t posZ = (int_t) MathUtils::floor_d(this->posZ * 32.);
    bool hasMoved = posX != lastPosX || posY != lastPosY || posZ != lastPosZ;
    bool isRelative = MathUtils::abs<int_t>(posX - lastPosX) < 128 && MathUtils::abs<int_t>(posY - lastPosY) < 128
        && MathUtils::abs<int_t>(posZ - lastPosZ) < 128 && onGround == lastOnGround && (ticks - 1) % 60 > 0;
    byte_t rotYaw = (byte_t) MathUtils::floor_f(this->rotYaw / 360. * 256.);
    byte_t rotPitch = (byte_t) MathUtils::floor_f(this->rotPitch / 360. * 256.);
    bool hasRotated = rotYaw != lastRotYaw || rotPitch != lastRotPitch;
    short_t motX = (short_t) MathUtils::floor_d(this->motX * 8000.);
    short_t motY = (short_t) MathUtils::floor_d(this->motY * 8000.);
    short_t motZ = (short_t) MathUtils::floor_d(this->motZ * 8000.);
    bool velocityChanged = motX != lastMotX && motY != lastMotY && motZ != lastMotZ && sendVelocityUpdates();
    if (hasMoved && isRelative && !hasRotated) {
        std::shared_ptr<PacketEntityMove> packet = std::make_shared<PacketEntityMove>();
        packet->entityId = entityId;
        packet->dX = posX - lastPosX;
        packet->dY = posY - lastPosY;
        packet->dZ = posZ - lastPosZ;
        packet->onGround = onGround;
        for (EntityPlayer *watcher : watchers)
            watcher->sendPacket(packet);
    } else if (!hasMoved && hasRotated) {
        std::shared_ptr<PacketEntityLook> packet = std::make_shared<PacketEntityLook>();
        packet->entityId = entityId;
        packet->yaw = rotYaw;
        packet->pitch = rotPitch;
        packet->onGround = onGround;
        for (EntityPlayer *watcher : watchers)
            watcher->sendPacket(packet);
    } else if (hasMoved && isRelative && hasRotated) {
        std::shared_ptr<PacketEntityMoveLook> packet = std::make_shared<PacketEntityMoveLook>();
        packet->entityId = entityId;
        packet->dX = posX - lastPosX;
        packet->dY = posY - lastPosY;
        packet->dZ = posZ - lastPosZ;
        packet->yaw = rotYaw;
        packet->pitch = rotPitch;
        packet->onGround = onGround;
        for (EntityPlayer *watcher : watchers)
            watcher->sendPacket(packet);
    } else if (hasMoved && !isRelative) {
        std::shared_ptr<PacketEntityTeleport> packet = std::make_shared<PacketEntityTeleport>();
        packet->entityId = entityId;
        packet->x = posX;
        packet->y = posY;
        packet->z = posZ;
        packet->yaw = rotYaw;
        packet->pitch = rotPitch;
        packet->onGround = onGround;
        for (EntityPlayer *watcher : watchers)
            watcher->sendPacket(packet);
    }
    if (velocityChanged) {
        std::shared_ptr<PacketEntityVelocity> packet = std::make_shared<PacketEntityVelocity>();
        packet->entityId = entityId;
        packet->velocityX = motX;
        packet->velocityY = motY;
        packet->velocityZ = motZ;
        for (EntityPlayer *watcher : watchers)
            watcher->sendPacket(packet);
    }
    if (dataWatcher.hasChanged()) {
        std::shared_ptr<PacketEntityMetadata> packet = std::make_shared<PacketEntityMetadata>(entityId, &dataWatcher);
        for (EntityPlayer *watcher : watchers)
            watcher->sendPacket(packet);
    }
    lastPosX = posX;
    lastPosY = posY;
    lastPosZ = posZ;
    lastOnGround = onGround;
    lastRotYaw = rotYaw;
    lastRotPitch = rotPitch;
    lastMotX = motX;
    lastMotY = motY;
    lastMotZ = motZ;
}

void Entity::setPosition() {
    posX = (boundingBox.minX + boundingBox.maxX) / 2.;
    posY = boundingBox.minY;
    posZ = (boundingBox.minZ + boundingBox.maxZ) / 2.;
}

void Entity::setSize(float_t width, float_t height) {
    this->width = width;
    this->height = height;
    setPosition(posX, posY, posZ);
}

int_t Entity::nextEntityId = 0;
