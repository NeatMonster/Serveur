#include "EntityLiving.h"

#include "PacketEntityHeadLook.h"
#include "EntityPlayer.h"

EntityLiving::EntityLiving(World *world) : Entity(world), headYaw(0), lastHeadYaw(0) {}

EntityLiving::~EntityLiving() {}

void EntityLiving::move(double_t x, double_t y, double_t z) {
    Entity::move(x, y, z);
}

void EntityLiving::rotate(float_t yaw, float_t pitch) {
    rotateHead(yaw);
    Entity::rotate(yaw, pitch);
}

void EntityLiving::setHeadRotation(float_t headYaw) {
    this->headYaw = mod<float_t>(headYaw, 360.);
}

void EntityLiving::rotateHead(float_t headYaw) {
    setHeadRotation(headYaw);
}

void EntityLiving::onTick() {
    Entity::onTick();
    int_t headYaw = (int_t) floor_f(this->headYaw / 360. * 256.);
    if (headYaw != lastHeadYaw)
        for (EntityPlayer *const &watcher : getWatchers()) {
            PacketEntityHeadLook *packet = new PacketEntityHeadLook();
            packet->entityId = entityId;
            packet->headYaw = headYaw;
            watcher->sendPacket(packet);
        }
    lastHeadYaw = headYaw;
}
