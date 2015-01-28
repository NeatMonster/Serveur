#include "ItemStack.h"

ItemStack::ItemStack(Item *item) : ItemStack(item, 0, 0) {}

ItemStack::ItemStack(Item *item, byte_t count) : ItemStack(item, count, 0) {}

ItemStack::ItemStack(Item *item, byte_t count, short_t damage) : item(item), count(count), damage(damage), tag(nullptr) {}

ItemStack::ItemStack(Block *block) : ItemStack(block, 0, 0) {}

ItemStack::ItemStack(Block *block, byte_t count) : ItemStack(block, count, 0) {}

ItemStack::ItemStack(Block *block, byte_t count, short_t damage) : item(Item::getItem(block)), count(count), damage(damage), tag(nullptr) {}

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

byte_t ItemStack::getCount() {
    return count;
}

void ItemStack::setCount(byte_t count) {
    this->count = count;
}

short_t ItemStack::getDamage() {
    return damage;
}

void ItemStack::setDamage(short_t damage) {
    this->damage = damage;
}

std::shared_ptr<NBTTagCompound> ItemStack::getTag() {
    return tag == nullptr ? nullptr : std::dynamic_pointer_cast<NBTTagCompound>(tag->clone());
}

void ItemStack::setTag(std::shared_ptr<NBTTagCompound> tag) {
    this->tag = std::dynamic_pointer_cast<NBTTagCompound>(tag->clone());
}

bool ItemStack::isStackable() {
    return getItem()->getMaxStackSize() > 1 && damage == 0;
}

std::shared_ptr<ItemStack> ItemStack::clone() {
    return std::make_shared<ItemStack>(this);
}
