#include "Slot.h"

Slot::Slot() {}

std::shared_ptr<ItemStack> Slot::getStack() {
    return stack == nullptr ? std::shared_ptr<ItemStack>() : stack->clone();
}

void Slot::setStack(std::shared_ptr<ItemStack> stack) {
    this->stack = stack == nullptr ? std::shared_ptr<ItemStack>() : stack->clone();
}
