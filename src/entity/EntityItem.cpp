#include "EntityItem.h"

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
