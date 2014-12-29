#include "Slot.h"

Slot::Slot() : stack(nullptr) {}

Slot::~Slot() {
    if (stack != nullptr)
        delete stack;
}

ItemStack *Slot::getStack() {
    return stack;
}

void Slot::setStack(ItemStack *stack) {
    if (this->stack != nullptr)
        delete this->stack;
    this->stack = stack;
}
