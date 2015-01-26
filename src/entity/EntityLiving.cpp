#include "EntityLiving.h"

#include "EntityPlayer.h"
#include "MathUtils.h"
#include "PacketEntityHeadLook.h"

EntityLiving::EntityLiving(World *world) : Entity(world), headYaw(0), lastHeadYaw(0) {}

EntityLiving::~EntityLiving() {}

void EntityLiving::setHeadRotation(float_t headYaw) {
    this->headYaw = MathUtils::mod<float_t>(headYaw, 360.);
}

void EntityLiving::jump() {}

void EntityLiving::onTick() {
    Entity::onTick();
    int_t headYaw = (int_t) MathUtils::floor_f(this->headYaw / 360. * 256.);
    if (headYaw != lastHeadYaw) {
        std::shared_ptr<PacketEntityHeadLook> packet = std::make_shared<PacketEntityHeadLook>();
        packet->entityId = entityId;
        packet->headYaw = headYaw;
        for (std::shared_ptr<EntityPlayer> watcher : getWatchers())
            watcher->sendPacket(packet);
    }
    lastHeadYaw = headYaw;
}
