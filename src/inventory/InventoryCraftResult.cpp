#include "InventoryCraftResult.h"

std::shared_ptr<ItemStack> InventoryCraftResult::getStack(short_t) {
    return stack;
}

void InventoryCraftResult::setStack(short_t, std::shared_ptr<ItemStack> stack) {
    this->stack = stack;
}

int InventoryCraftResult::getInventoryStackLimit() {
    return 64;
}
