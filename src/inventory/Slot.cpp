#include "Slot.h"

Slot::Slot(Inventory &inventory, short_t slotIndex) : inventory(inventory), slotIndex(slotIndex) {}

Slot::~Slot() {}

std::shared_ptr<ItemStack> Slot::getStack() {
    return inventory.getStack(slotIndex);
}

void Slot::setStack(std::shared_ptr<ItemStack> stack) {
    inventory.setStack(slotIndex, stack);
}
