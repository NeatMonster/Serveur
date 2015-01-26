#include "EntityItem.h"

#include "Item.h"
#include "MathUtils.h"
#include "PacketSpawnObject.h"
#include "World.h"

EntityItem::EntityItem(World *world, ItemStack *stack) : Entity(world), stack(stack), pickupDelay(10) {
    setSize(0.25, 0.25);
    dataWatcher.setItemStack(10, stack->clone());
}

EntityItem::~EntityItem() {
    delete stack;
}

void EntityItem::onCollision(EntityPlayer *player) {
    // TODO Permettre aux joueurs de ramasser les items
}

void EntityItem::onTick() {
    Entity::onTick();
    if (pickupDelay > 0 && pickupDelay != 32767)
        pickupDelay--;
    double_t prevX = posX, prevY = posY, prevZ = posZ;
    motY -= 0.04;
    noClip = pushOutOfBlocks(posX, (boundingBox.minY + boundingBox.maxY) / 2, posZ);
    move(motX, motY, motZ);
    bool hasMoved = (int_t) prevX != (int_t) posX || (int_t) prevY != (int_t) posY || (int_t) prevZ != (int_t) posZ;
    if (hasMoved || ticks % 25 == 0)
        searchForItems();
    motX *= 0.98 * (onGround ? 0.6 : 1);
    motY *= 0.98;
    motZ *= 0.98 * (onGround ? 0.6 : 1);
    if (onGround)
        motY *= -0.5;
    if (ticks >= 1200)
        setDead();
}

std::shared_ptr<ServerPacket> EntityItem::getSpawnPacket() {
    return std::make_shared<PacketSpawnObject>(this, 1);
}

void EntityItem::searchForItems() {
    std::vector<Entity*> entities = world->getEntityCollisions(getBoundingBox().clone().expand(0.5, 0, 0.5), [this] (Entity *entity) {
        return entity != this && entity->getType() == Type::ITEM;
    });
    for (Entity *entity : entities)
        combineItems((EntityItem*) entity);
}

bool EntityItem::combineItems(EntityItem *other) {
    if (other == this || isDead() || other->isDead()
        || pickupDelay == 32767 || other->pickupDelay == 32767
        || ticks == -32768 || other->ticks == -32768
        || stack->getType() != other->stack->getType()
        || stack->getAmount() + stack->getAmount() > Item::getItem(stack->getType())->getMaxStackSize()
        || stack->getDamage() != other->stack->getDamage()
        || stack->getNBT() != nullptr ^ other->stack->getNBT() != nullptr
        || (stack->getNBT() != nullptr && !stack->getNBT()->equals(other->stack->getNBT())))
        return false;
    if (stack->getAmount() > other->stack->getAmount())
        return other->combineItems(this);
    other->stack->setAmount(other->stack->getAmount() + stack->getAmount());
    other->pickupDelay = MathUtils::max(other->pickupDelay, pickupDelay);
    other->ticks = MathUtils::min(other->ticks, ticks);
    other->dataWatcher.setItemStack(10, other->stack);
    setDead();
    return true;
}
