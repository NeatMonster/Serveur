#include "EntityItem.h"

#include "Metadata.h"
#include "PacketEntityMetadata.h"
#include "PacketSpawnObject.h"

EntityItem::EntityItem(World *world, ItemStack *stack) : Entity(world), stack(stack) {
    setSize(0.25, 0.25);
}

EntityItem::~EntityItem() {
    delete stack;
}

void EntityItem::onTick() {
    Entity::onTick();
    motY -= 0.04;
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

ServerPacket *EntityItem::getMetadataPacket() {
    Metadata *metadata = new Metadata();
    metadata->setItemStack(10, stack->clone());
    return new PacketEntityMetadata(entityId, metadata);
}
