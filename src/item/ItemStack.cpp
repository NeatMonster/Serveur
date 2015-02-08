#include "ItemStack.h"

ItemStack::ItemStack(Item *item) : ItemStack(item, 0, 0) {}

ItemStack::ItemStack(Item *item, count_t count) : ItemStack(item, count, 0) {}

ItemStack::ItemStack(Item *item, count_t count, ushort_t damage) : item(item), count(count), damage(damage), tag(nullptr) {}

ItemStack::ItemStack(Block *block) : ItemStack(block, 0, 0) {}

ItemStack::ItemStack(Block *block, count_t count) : ItemStack(block, count, 0) {}

ItemStack::ItemStack(Block *block, count_t count, ushort_t damage) : item(Item::getItem(block)), count(count), damage(damage), tag(nullptr) {}

ItemStack::ItemStack(ItemStack *stack) : item(stack->item), count(stack->count), damage(stack->damage) {
    if (stack->tag == nullptr)
        tag = nullptr;
    else
        tag = std::dynamic_pointer_cast<NBTTagCompound>(stack->tag->clone());
}

Item *ItemStack::getItem() {
    return item;
}

void ItemStack::setItem(Item *item) {
    this->item = item;
}

count_t ItemStack::getCount() {
    return count;
}

void ItemStack::setCount(count_t count) {
    this->count = count;
}

ushort_t ItemStack::getDamage() {
    return damage;
}

void ItemStack::setDamage(ushort_t damage) {
    this->damage = damage;
}

std::shared_ptr<NBTTagCompound> ItemStack::getTag() {
    return tag;
}

void ItemStack::setTag(std::shared_ptr<NBTTagCompound> tag) {
    this->tag = tag;
}

bool ItemStack::hasTag() {
    return tag != nullptr;
}

bool ItemStack::isDamageable() {
    return item != nullptr && item->getMaxDamage() > 0 && (tag == nullptr || tag->get("Unbreakable")->asByte() != 0);
}

bool ItemStack::isDamaged() {
    return isDamageable() && damage > 0;
}

bool ItemStack::isStackable() {
    return getMaxStackSize() > 1 && (!isDamageable() || !isDamaged());
}

count_t ItemStack::getMaxStackSize() {
    return getItem()->getMaxStackSize();
}

void ItemStack::onCrafting(EntityPlayer *player) {
    item->onCreated(shared_from_this(), player);
}

std::shared_ptr<ItemStack> ItemStack::splitStack(count_t amount) {
    std::shared_ptr<ItemStack> stack = std::make_shared<ItemStack>(item, amount, damage);
    if (tag != nullptr)
        stack->setTag(std::dynamic_pointer_cast<NBTTagCompound>(tag->clone()));
    count -= amount;
    return stack;
}

bool ItemStack::equals(std::shared_ptr<ItemStack> stack) {
    return equals(stack, true);
}

bool ItemStack::equals(std::shared_ptr<ItemStack> stack, bool sizeMatters) {
    return stack != nullptr && item == stack->getItem() && (!sizeMatters || count == stack->getCount())
        && (!item->getHasSubtypes() || damage == stack->getDamage())
        && ((tag == nullptr && stack->getTag() == nullptr) || (tag != nullptr && tag->equals(stack->getTag())));
}

std::shared_ptr<ItemStack> ItemStack::clone() {
    return std::make_shared<ItemStack>(this);
}
