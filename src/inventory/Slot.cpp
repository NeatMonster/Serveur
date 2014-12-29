#include "Slot.h"

Slot::Slot() : stack(nullptr) {}

Slot::~Slot() {
    if (this->stack != nullptr)
        delete this->stack;
}

ItemStack *Slot::getStack() {
    return this->stack;
}

void Slot::setStack(ItemStack *stack) {
    if (this->stack != nullptr)
        delete this->stack;
    this->stack = stack;
}
