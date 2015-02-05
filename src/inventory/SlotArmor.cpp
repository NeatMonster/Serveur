#include "SlotArmor.h"

SlotArmor::SlotArmor(Inventory &inventory, short_t index) : Slot(inventory, index) {}

bool SlotArmor::isValid(std::shared_ptr<ItemStack> stack) {
    return false; // TODO Autoriser les armures une fois implémentées
}

int SlotArmor::getSlotStackLimit() {
    return 1;
}
