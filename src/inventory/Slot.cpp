#include "Slot.h"

Slot::Slot(Inventory &inventory, short_t slotIndex) : inventory(inventory), slotIndex(slotIndex) {}

Slot::~Slot() {}

bool Slot::hasStack() {
    return getStack() != nullptr;
}

std::shared_ptr<ItemStack> Slot::getStack() {
    return inventory.getStack(slotIndex);
}

void Slot::putStack(std::shared_ptr<ItemStack> stack) {
    inventory.setStack(slotIndex, stack);
}

void Slot::onSlotChange(std::shared_ptr<ItemStack> oldStack, std::shared_ptr<ItemStack> newStack) {
    if (oldStack != nullptr && newStack != nullptr && oldStack->getItem() == newStack->getItem()) {
        int amount = newStack->getCount() - oldStack->getCount();
        if (amount > 0)
            onCrafting(oldStack, amount);
    }
}

bool Slot::canTakeStack(EntityPlayer*) {
    return true;
}

std::shared_ptr<ItemStack> Slot::decrStackSize(int amount) {
    inventory
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

void Slot::onPickupFromSlot(EntityPlayer*, std::shared_ptr<ItemStack>) {}

void Slot::onCrafting(std::shared_ptr<ItemStack>) {}

void Slot::onCrafting(std::shared_ptr<ItemStack> stack, int) {}
