#include "LivingEntity.h"

#include "PacketEntityHeadLook.h"
#include "Player.h"

LivingEntity::LivingEntity(World *world) : Entity(world), headYaw(0), lastHeadYaw(0) {}

LivingEntity::~LivingEntity() {}

void LivingEntity::setPosition(double_t x, double_t y, double_t z) {
    Entity::setPosition(x, y, z);
}

void LivingEntity::setRotation(float_t yaw, float_t pitch) {
    Entity::setRotation(yaw, pitch);
}

void LivingEntity::setHeadRotation(float_t headYaw) {
    this->headYaw = mod<float_t>(headYaw, 360.);
}

void LivingEntity::onTick() {
    Entity::onTick();
    int_t headYaw = (int_t) floor(this->headYaw / 360. * 256.);
    if (headYaw != lastHeadYaw)
        for (Player *const &watcher : getWatchers()) {
            PacketEntityHeadLook *packet = new PacketEntityHeadLook();
            packet->entityId = entityId;
            packet->headYaw = headYaw;
            watcher->sendPacket(packet);
        }
    lastHeadYaw = headYaw;
}
