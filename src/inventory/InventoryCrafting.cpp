#include "InventoryCrafting.h"

InventoryCrafting::InventoryCrafting(Container &eventHandler, int size) : eventHandler(eventHandler) {
    stacks = std::vector<std::shared_ptr<ItemStack>>(size * size, nullptr);
}

std::shared_ptr<ItemStack> InventoryCrafting::getStack(short_t index) {
    return index >= stacks.size() ? nullptr : stacks[index];
}

void InventoryCrafting::setStack(short_t index, std::shared_ptr<ItemStack> stack) {
    if (index < stacks.size())
        stacks[index] = stack;
}

std::shared_ptr<ItemStack> InventoryCrafting::decrStackSize(short_t index, int count) {
    if (stacks[index] != nullptr) {
        if (stacks[index]->getCount() <= count) {
            std::shared_ptr<ItemStack> stack = stacks[index];
            stacks[index] = nullptr;
            eventHandler.onCraftMatrixChanged(*this);
            return stack;
        } else {
            std::shared_ptr<ItemStack> stack = stacks[index]->splitStack(count);
            if (stacks[index]->getCount() == 0)
                stacks[index] = nullptr;
            eventHandler.onCraftMatrixChanged(*this);
            return stack;
        }
    } else
        return nullptr;
}

int InventoryCrafting::getInventoryStackLimit() {
    return 64;
}
