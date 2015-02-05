#include "Slot.h"

Slot::Slot(Inventory &inventory, short_t slotIndex) : inventory(inventory), slotIndex(slotIndex) {}

Slot::~Slot() {}

bool Slot::hasStack() {
    return getStack() != nullptr;
}

std::shared_ptr<ItemStack> Slot::getStack() {
    return inventory.getStack(slotIndex);
}

void Slot::setStack(std::shared_ptr<ItemStack> stack) {
    inventory.setStack(slotIndex, stack);
}

bool Slot::isValid(std::shared_ptr<ItemStack>) {
    return true;
}

int Slot::getSlotMaxSize(std::shared_ptr<ItemStack> stack) {
    return getSlotStackLimit();
}

int Slot::getSlotStackLimit() {
    return inventory.getInventoryStackLimit();
}
