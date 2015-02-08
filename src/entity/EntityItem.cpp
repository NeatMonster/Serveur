#include "EntityItem.h"

#include "Item.h"
#include "MathUtils.h"
#include "PacketCollectItem.h"
#include "PacketSpawnObject.h"
#include "World.h"

EntityItem::EntityItem(World *world, std::shared_ptr<ItemStack> stack) : Entity(world), age(0), pickupDelay(10) {
    setSize(0.25, 0.25);
    setItem(stack);
}

void EntityItem::fromCreative() {
    age = 4800;
}

void EntityItem::onCollision(EntityPlayer *player) {
    std::shared_ptr<ItemStack> stack = getItem();
    if (pickupDelay == 0 && player->getInventory().addStack(stack)) {
        world->playSound(posX, posY, posZ, "random.pop", 0.2, ((MathUtils::random_f() - MathUtils::random_f()) * 0.7 + 1) * 2);
        std::shared_ptr<PacketCollectItem> packet = std::make_shared<PacketCollectItem>();
        packet->collectedId = entityId;
        packet->collectorId = player->getEntityId();
        player->sendPacket(packet);
        for (EntityPlayer *watcher : player->getWatchers())
            watcher->sendPacket(packet);
        setItem(stack);
        if (stack->getCount() <= 0)
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
        --pickupDelay;
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
    if (age != -32768)
        ++age;
    if (age >= 6000)
        setDead();
}

std::shared_ptr<ServerPacket> EntityItem::getSpawnPacket() {
    return std::make_shared<PacketSpawnObject>(this, 1);
}

void EntityItem::searchForItems() {
    std::vector<Entity*> entities = world->getEntityCollisions(getBoundingBox().clone().expand(0.5, 0, 0.5),
    [] (Entity *entity) {
        return entity->getType() == Type::ITEM;
    });
    for (Entity *entity : entities)
        combineItems((EntityItem*) entity);
}

bool EntityItem::combineItems(EntityItem *other) {
    std::shared_ptr<ItemStack> stack = getItem();
    std::shared_ptr<ItemStack> otherStack = other->getItem();
    if (other == this || isDead() || other->isDead()
        || pickupDelay == 32767 || other->pickupDelay == 32767
        || age == -32768 || other->age == -32768
        || !stack->equals(otherStack, false)
        || stack->getCount() + stack->getCount() > stack->getMaxStackSize())
        return false;
    if (stack->getCount() > otherStack->getCount())
        return other->combineItems(this);
    otherStack->setCount(otherStack->getCount() + stack->getCount());
    other->setItem(otherStack);
    other->pickupDelay = MathUtils::max(other->pickupDelay, pickupDelay);
    other->ticks = MathUtils::min(other->ticks, ticks);
    setDead();
    return true;
}
