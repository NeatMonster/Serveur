#include "Entity.h"

#include "Chunk.h"
#include "PacketEntityLook.h"
#include "PacketEntityMove.h"
#include "PacketEntityMoveLook.h"
#include "PacketEntityTeleport.h"
#include "Player.h"
#include "World.h"

Entity::Entity(World *world) : world(world), ticks(0), dead(false), x(0), y(0), z(0), yaw(0), pitch(0), onGround(false),
        lastX(0), lastY(0), lastZ(0), lastYaw(0), lastPitch(0), lastOnGround(false) {
    entityId = nextEntityId++;
}

Entity::~Entity() {}

int_t Entity::getEntityId() {
    return entityId;
}

Chunk *Entity::getChunk() {
    return world->getChunk((int_t) floor_d(x) >> 4, (int_t) floor_d(z) >> 4);
}

World *Entity::getWorld() {
    return world;
}

std::set<Player*> Entity::getWatchers() {
    std::set<Player*> watchers;
    int_t xChunk = (int_t) floor(x) >> 4;
    int_t zChunk = (int_t) floor(z) >> 4;
    for (int x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++) {
            Chunk *chunk = world->tryGetChunk(xChunk + x, zChunk + z);
            if (chunk != nullptr)
                for (Player *const &watcher : chunk->getPlayers())
                    if (watcher->getEntityId() != getEntityId())
                        watchers.insert(watcher);
        }
    return watchers;
}

double_t Entity::getX() {
    return x;
}

double_t Entity::getY() {
    return y;
}

double_t Entity::getZ() {
    return z;
}

float_t Entity::getYaw() {
    return yaw;
}

float_t Entity::getPitch() {
    return pitch;
}

void Entity::setPosition(double_t x, double_t y, double_t z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Entity::move(double_t x, double_t y, double_t z) {
    setPosition(x, y, z);
}

void Entity::setRotation(float_t yaw, float_t pitch) {
    this->yaw = mod<float_t>(yaw, 360.);
    this->pitch = mod<float_t>(pitch, 360.);
}

void Entity::rotate(float_t yaw, float_t pitch) {
    setRotation(yaw, pitch);
}

bool Entity::isDead() {
    return dead;
}

void Entity::setDead() {
    dead = true;
}

void Entity::onTick() {
    ticks++;
    int_t x = (int_t) floor_d(this->x * 32.);
    int_t y = (int_t) floor_d(this->y * 32.);
    int_t z = (int_t) floor_d(this->z * 32.);
    byte_t yaw = (byte_t) floor_f(this->yaw / 360. * 256.);
    byte_t pitch = (byte_t) floor_f(this->pitch / 360. * 256.);
    bool hasMoved = x != lastX || y != lastY || z != lastZ;
    bool hasRotated = yaw != lastYaw || pitch != lastPitch;
    bool isRelative = abs<int_t>(x - lastX) < 128 && abs<int_t>(y - lastY) < 128
        && abs<int_t>(z - lastZ) < 128 && onGround != lastOnGround && ticks % 60 > 0;
    if (hasMoved && isRelative && !hasRotated)
        for (Player *const &watcher : getWatchers()) {
            PacketEntityMove *packet = new PacketEntityMove();
            packet->entityId = entityId;
            packet->dX = x - lastX;
            packet->dY = y - lastY;
            packet->dZ = z - lastZ;
            packet->onGround = onGround;
            watcher->sendPacket(packet);
        }
    else if (!hasMoved && hasRotated)
        for (Player *const &watcher : getWatchers()) {
            PacketEntityLook *packet = new PacketEntityLook();
            packet->entityId = entityId;
            packet->yaw = yaw;
            packet->pitch = pitch;
            packet->onGround = onGround;
            watcher->sendPacket(packet);
        }
    else if (hasMoved && isRelative && hasRotated)
        for (Player *const &watcher : getWatchers()) {
            PacketEntityMoveLook *packet = new PacketEntityMoveLook();
            packet->entityId = entityId;
            packet->dX = x - lastX;
            packet->dY = y - lastY;
            packet->dZ = z - lastZ;
            packet->yaw = yaw;
            packet->pitch = pitch;
            packet->onGround = onGround;
            watcher->sendPacket(packet);
        }
    else if (hasMoved && !isRelative) {
        for (Player *const &watcher : getWatchers()) {
            PacketEntityTeleport *packet = new PacketEntityTeleport();
            packet->entityId = entityId;
            packet->x = x;
            packet->y = y;
            packet->z = z;
            packet->yaw = yaw;
            packet->pitch = pitch;
            packet->onGround = onGround;
            watcher->sendPacket(packet);
        }
    }
    lastX = x;
    lastY = y;
    lastZ = z;
    lastYaw = yaw;
    lastPitch = pitch;
    lastOnGround = onGround;
}

int_t Entity::nextEntityId = 0;
