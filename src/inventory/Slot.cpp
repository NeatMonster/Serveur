#include "Slot.h"

Slot::Slot() : stack(nullptr) {}

ItemStack *Slot::getStack() {
    return stack;
}

void Slot::setStack(ItemStack *stack) {
    delete this->stack;
    this->stack = stack;
}
