#include "Inventory.h"

Inventory::Inventory() {}

Inventory::~Inventory() {
    for (Slot *slot : slots)
        delete slot;
}

void Inventory::putStack(short_t slot, ItemStack *stack) {
    getSlot(slot)->setStack(stack);
}

void Inventory::addSlot(Slot *slot) {
    slots.push_back(slot);
}

Slot *Inventory::getSlot(short_t slot) {
    return slots[slot];
}
