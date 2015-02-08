#include "InventoryCraftResult.h"

std::shared_ptr<ItemStack> InventoryCraftResult::getStack(short_t) {
    return stack;
}

void InventoryCraftResult::setStack(short_t, std::shared_ptr<ItemStack> stack) {
    this->stack = stack;
}

std::shared_ptr<ItemStack> InventoryCraftResult::decrStackSize(short_t index, count_t count) {
    if (stack != nullptr) {
        std::shared_ptr<ItemStack> stack = this->stack;
        this->stack = nullptr;
        return stack;
    } else
        return nullptr;
}

count_t InventoryCraftResult::getInventoryStackLimit() {
    return 64;
}
