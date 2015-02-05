#include "InventoryCrafting.h"

InventoryCrafting::InventoryCrafting(int size) {
    stacks = std::vector<std::shared_ptr<ItemStack>>(size * size, nullptr);
}

std::shared_ptr<ItemStack> InventoryCrafting::getStack(short_t index) {
    return index >= stacks.size() ? nullptr : stacks[index];
}

void InventoryCrafting::setStack(short_t index, std::shared_ptr<ItemStack> stack) {
    if (index < stacks.size())
        stacks[index] = stack;
}

int InventoryCrafting::getInventoryStackLimit() {
    return 64;
}
