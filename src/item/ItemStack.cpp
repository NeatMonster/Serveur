#include "ItemStack.h"

ItemStack::ItemStack(short_t type) : ItemStack(type, 0, 0) {}

ItemStack::ItemStack(short_t type, byte_t amount) : ItemStack(type, amount, 0) {}

ItemStack::ItemStack(short_t type, byte_t amount, short_t damage) : type(type), amount(amount), damage(damage), nbt(nullptr) {}

ItemStack::ItemStack(ItemStack *stack) : type(stack->type), amount(stack->amount), damage(stack->damage) {
    nbt = stack->nbt == nullptr ? nullptr : stack->nbt->clone();
}

ItemStack::~ItemStack() {
    if (nbt != nullptr)
        delete nbt;
}

short_t ItemStack::getType() {
    return type;
}

void ItemStack::setType(short_t type) {
    this->type = type;
}

byte_t ItemStack::getAmount() {
    return amount;
}

void ItemStack::setAmount(byte_t amount) {
    this->amount = amount;
}

short_t ItemStack::getDamage() {
    return damage;
}

void ItemStack::setDamage(short_t damage) {
    this->damage = damage;
}

NBTTagCompound *ItemStack::getNBT() {
    return nbt;
}

std::shared_ptr<ItemStack> ItemStack::clone() {
    return std::make_shared<ItemStack>(this);
}
