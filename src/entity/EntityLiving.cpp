#include "EntityLiving.h"

#include "EntityPlayer.h"
#include "MathUtils.h"
#include "PacketEntityHeadLook.h"

EntityLiving::EntityLiving(World *world) : Entity(world), headYaw(0), lastHeadYaw(0) {
    dataWatcher.setFloat(6, getMaxHealth());
}

EntityLiving::~EntityLiving() {}

void EntityLiving::setHeadRotation(float_t headYaw) {
    this->headYaw = MathUtils::mod<float_t>(headYaw, 360.);
}

void EntityLiving::jump() {}

void EntityLiving::onTick() {
    Entity::onTick();
    if (ticks % getUpdateFrequency() > 0)
        return;
    int_t headYaw = (int_t) MathUtils::floor_f(this->headYaw / 360. * 256.);
    if (headYaw != lastHeadYaw) {
        std::shared_ptr<PacketEntityHeadLook> packet = std::make_shared<PacketEntityHeadLook>();
        packet->entityId = entityId;
        packet->headYaw = headYaw;
        for (EntityPlayer *watcher : getWatchers())
            watcher->sendPacket(packet);
    }
    lastHeadYaw = headYaw;
}

void EntityLiving::setHealth(float_t amount) {
    dataWatcher.setFloat(6, MathUtils::clamp(amount, 0.0F, getMaxHealth()));
}

float_t EntityLiving::getHealth() {
    return getDataWatcher().getFloat(6);
}

float_t EntityLiving::getMaxHealth() {
    return 20.0F; //TODO Récupérer cette valeur en fonction de l'entité.
}

void EntityLiving::heal(float_t amount) {
    if(getHealth() > 0.0F)
        setHealth(getHealth() + amount);
}
