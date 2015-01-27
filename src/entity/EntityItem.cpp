#include "EntityItem.h"

#include "Item.h"
#include "MathUtils.h"
#include "PacketCollectItem.h"
#include "PacketSpawnObject.h"
#include "World.h"

EntityItem::EntityItem(World *world, std::shared_ptr<ItemStack> stack) : Entity(world), pickupDelay(10) {
    setSize(0.25, 0.25);
    setItem(stack);
}

void EntityItem::onCollision(std::shared_ptr<EntityPlayer> player) {
    if (pickupDelay == 0) { // TODO Ajouter l'item à l'inventaire
        world->playSound(posX, posY, posZ, "random.pop", 0.2, ((MathUtils::random_f() - MathUtils::random_f()) * 0.7 + 1) * 2);
        std::shared_ptr<PacketCollectItem> packet = std::make_shared<PacketCollectItem>();
        packet->collectedId = entityId;
        packet->collectorId = player->getEntityId();
        player->sendPacket(packet);
        for (std::shared_ptr<EntityPlayer> watcher : player->getWatchers())
            watcher->sendPacket(packet);
        setDead();
    }
}

std::shared_ptr<ItemStack> EntityItem::getItem() {
    return dataWatcher.getItemStack(10);
}

void EntityItem::setItem(std::shared_ptr<ItemStack> stack) {
    dataWatcher.setItemStack(10, stack);
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
    std::vector<std::shared_ptr<Entity>> entities = world->getEntityCollisions(getBoundingBox().clone().expand(0.5, 0, 0.5),
    [] (std::shared_ptr<Entity> entity) {
        return entity->getType() == Type::ITEM;
    });
    for (std::shared_ptr<Entity> entity : entities)
        combineItems(std::dynamic_pointer_cast<EntityItem>(entity));
}

bool EntityItem::combineItems(std::shared_ptr<EntityItem> other) {
    std::shared_ptr<ItemStack> stack = getItem();
    std::shared_ptr<ItemStack> otherStack = other->getItem();
    if (other.get() == this || isDead() || other->isDead()
        || pickupDelay == 32767 || other->pickupDelay == 32767
        || ticks == -32768 || other->ticks == -32768
        || stack->getType() != otherStack->getType()
        || stack->getAmount() + stack->getAmount() > Item::getItem(stack->getType())->getMaxStackSize()
        || stack->getDamage() != otherStack->getDamage()
        || stack->getNBT() != nullptr ^ otherStack->getNBT() != nullptr
        || (stack->getNBT() != nullptr && !stack->getNBT()->equals(otherStack->getNBT())))
        return false;
    if (stack->getAmount() > otherStack->getAmount())
        return other->combineItems(std::dynamic_pointer_cast<EntityItem>(shared_from_this()));
    otherStack->setAmount(otherStack->getAmount() + stack->getAmount());
    other->setItem(otherStack);
    other->pickupDelay = MathUtils::max(other->pickupDelay, pickupDelay);
    other->ticks = MathUtils::min(other->ticks, ticks);
    setDead();
    return true;
}
