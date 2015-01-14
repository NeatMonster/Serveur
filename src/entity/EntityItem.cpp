#include "EntityItem.h"

#include "Metadata.h"
#include "PacketEntityMetadata.h"
#include "PacketSpawnObject.h"

EntityItem::EntityItem(World *world, ItemStack *stack) : Entity(world), stack(stack) {}

EntityItem::~EntityItem() {
    delete stack;
}

Entity::Type EntityItem::getType() {
    return Type::ITEM;
}

void EntityItem::onTick() {
    Entity::onTick();
    if (ticks >= 1200)
        setDead();
}

ServerPacket *EntityItem::getSpawnPacket() {
    return new PacketSpawnObject(this);
}

ServerPacket *EntityItem::getMetadataPacket() {
    Metadata *metadata = new Metadata();
    metadata->setItemStack(10, stack->clone());
    return new PacketEntityMetadata(entityId, metadata);
}
