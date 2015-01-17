#include "Entity.h"

#include "Chunk.h"
#include "EntityPlayer.h"
#include "PacketEntityLook.h"
#include "PacketEntityMove.h"
#include "PacketEntityMoveLook.h"
#include "PacketEntityTeleport.h"
#include "PacketEntityVelocity.h"
#include "World.h"

Entity::Entity(World *world) : world(world), ticks(0), dead(false), posX(0), posY(0), posZ(0), rotYaw(0), rotPitch(0),
    motX(0), motY(0), motZ(0), onGround(false), lastPosX(0), lastPosY(0), lastPosZ(0), lastRotYaw(0), lastRotPitch(0),
    lastMotX(0), lastMotY(0), lastMotZ(0), lastOnGround(false) {
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

void Entity::setPosition(double_t x, double_t y, double_t z) {
    posX = x;
    posY = y;
    posZ = z;
}

void Entity::move(double_t x, double_t y, double_t z) {
    int_t xOld = (int_t) floor(posX) >> 4;
    int_t zOld = (int_t) floor(posZ) >> 4;
    int_t xNew = (int_t) floor(x) >> 4;
    int_t zNew = (int_t) floor(z) >> 4;
    if (xOld != xNew || zOld != zNew) {
        world->getChunk(xOld, zOld)->removeEntity(this);
        world->getChunk(xNew, zNew)->addEntity(this);
    }
    setPosition(x, y, z);
}

void Entity::setRotation(float_t yaw, float_t pitch) {
    rotYaw = mod<float_t>(yaw, 360.);
    rotPitch = mod<float_t>(pitch, 360.);
}

void Entity::rotate(float_t yaw, float_t pitch) {
    setRotation(yaw, pitch);
}

Chunk *Entity::getChunk() {
    return world->getChunk((int_t) floor_d(posX) >> 4, (int_t) floor_d(posZ) >> 4);
}

std::unordered_set<EntityPlayer*> Entity::getWatchers() {
    std::unordered_set<EntityPlayer*> watchers;
    int_t xChunk = (int_t) floor(posX) >> 4;
    int_t zChunk = (int_t) floor(posZ) >> 4;
    for (int x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++) {
            Chunk *chunk = world->tryGetChunk(xChunk + x, zChunk + z);
            if (chunk != nullptr)
                for (EntityPlayer *const &watcher : chunk->getPlayers())
                    if (watcher->getEntityId() != getEntityId())
                        watchers.insert(watcher);
        }
    return watchers;
}

void Entity::onTick() {
    ticks++;
    int_t posX = (int_t) floor_d(this->posX * 32.);
    int_t posY = (int_t) floor_d(this->posY * 32.);
    int_t posZ = (int_t) floor_d(this->posZ * 32.);
    byte_t rotYaw = (byte_t) floor_f(this->rotYaw / 360. * 256.);
    byte_t rotPitch = (byte_t) floor_f(this->rotPitch / 360. * 256.);
    short_t motX = (short_t) floor_d(this->motX * 8000.);
    short_t motY = (short_t) floor_d(this->motY * 8000.);
    short_t motZ = (short_t) floor_d(this->motZ * 8000.);
    bool hasMoved = posX != lastPosX || posY != lastPosY || posZ != lastPosZ;
    bool hasRotated = rotYaw != lastRotYaw || rotPitch != lastRotPitch;
    bool isRelative = abs<int_t>(posX - lastPosX) < 128 && abs<int_t>(posY - lastPosY) < 128
        && abs<int_t>(posZ - lastPosZ) < 128 && onGround != lastOnGround && ticks % 60 > 0;
    bool velocityChanged = motX != lastMotX && motY != lastMotY && motZ != lastMotZ;
    if (hasMoved && isRelative && !hasRotated)
        for (EntityPlayer *const &watcher : getWatchers()) {
            PacketEntityMove *packet = new PacketEntityMove();
            packet->entityId = entityId;
            packet->dX = posX - lastPosX;
            packet->dY = posY - lastPosY;
            packet->dZ = posZ - lastPosZ;
            packet->onGround = onGround;
            watcher->sendPacket(packet);
        }
    else if (!hasMoved && hasRotated)
        for (EntityPlayer *const &watcher : getWatchers()) {
            PacketEntityLook *packet = new PacketEntityLook();
            packet->entityId = entityId;
            packet->yaw = rotYaw;
            packet->pitch = rotPitch;
            packet->onGround = onGround;
            watcher->sendPacket(packet);
        }
    else if (hasMoved && isRelative && hasRotated)
        for (EntityPlayer *const &watcher : getWatchers()) {
            PacketEntityMoveLook *packet = new PacketEntityMoveLook();
            packet->entityId = entityId;
            packet->dX = posX - lastPosX;
            packet->dY = posY - lastPosY;
            packet->dZ = posZ - lastPosZ;
            packet->yaw = rotYaw;
            packet->pitch = rotPitch;
            packet->onGround = onGround;
            watcher->sendPacket(packet);
        }
    else if (hasMoved && !isRelative) {
        for (EntityPlayer *const &watcher : getWatchers()) {
            PacketEntityTeleport *packet = new PacketEntityTeleport();
            packet->entityId = entityId;
            packet->x = posX;
            packet->y = posY;
            packet->z = posZ;
            packet->yaw = rotYaw;
            packet->pitch = rotPitch;
            packet->onGround = onGround;
            watcher->sendPacket(packet);
        }
    }
    if (velocityChanged)
        for (EntityPlayer *const &watcher : getWatchers()) {
            PacketEntityVelocity *packet = new PacketEntityVelocity();
            packet->entityId = entityId;
            packet->velocityX = motX;
            packet->velocityY = motY;
            packet->velocityZ = motZ;
            watcher->sendPacket(packet);
        }
    lastPosX = posX;
    lastPosY = posY;
    lastPosZ = posZ;
    lastRotYaw = rotYaw;
    lastRotPitch = rotPitch;
    lastOnGround = onGround;
}

int_t Entity::nextEntityId = 0;
