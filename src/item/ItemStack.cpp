#include "ItemStack.h"

ItemStack::ItemStack(short_t type) : ItemStack(type, 0, 0) {}

ItemStack::ItemStack(short_t type, byte_t amount) : ItemStack(type, amount, 0) {}

ItemStack::ItemStack(short_t type, byte_t amount, short_t damage) : type(type), amount(amount), damage(damage), nbt(nullptr) {}

ItemStack::ItemStack(ItemStack *stack) : type(stack->type), amount(stack->amount), damage(stack->damage) {
    nbt = (stack->nbt == nullptr) ? nullptr : stack->nbt->clone();
};

ItemStack::~ItemStack() {
    if (nbt != nullptr)
        delete nbt;
}

short_t ItemStack::getType() {
    return type;
}

byte_t ItemStack::getAmount() {
    return amount;
}

short_t ItemStack::getDamage() {
    return damage;
}

NBTTagCompound *ItemStack::getNBT() {
    return nbt;
}

ItemStack *ItemStack::clone() {
    return new ItemStack(this);
}
