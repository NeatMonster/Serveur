#include "SlotCrafting.h"

SlotCrafting::SlotCrafting(EntityPlayer *player, InventoryCrafting &craftMatrix, Inventory &inventory, short_t index) :
    Slot(inventory, index), player(player), craftMatrix(craftMatrix) {}

bool SlotCrafting::isValid(std::shared_ptr<ItemStack>) {
    return false;
}
