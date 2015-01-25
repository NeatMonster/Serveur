#include "EntityItem.h"

#include "PacketSpawnObject.h"

EntityItem::EntityItem(World *world, ItemStack *stack) : Entity(world), stack(stack) {
    setSize(0.25, 0.25);
    dataWatcher.setItemStack(10, stack->clone());
}

EntityItem::~EntityItem() {
    delete stack;
}

void EntityItem::onTick() {
    Entity::onTick();
    motY -= 0.04;
    noClip = pushOutOfBlocks(posX, (boundingBox.minY + boundingBox.maxY) / 2, posZ);
    move(motX, motY, motZ);
    motX *= 0.98 * (onGround ? 0.6 : 1);
    motY *= 0.98;
    motZ *= 0.98 * (onGround ? 0.6 : 1);
    if (onGround)
        motY *= -0.5;
    if (ticks >= 1200)
        setDead();
}

ServerPacket *EntityItem::getSpawnPacket() {
    return new PacketSpawnObject(this, 1);
}
