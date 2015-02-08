#include "SlotCrafting.h"

SlotCrafting::SlotCrafting(EntityPlayer *player, InventoryCrafting &craftMatrix, Inventory &inventory, short_t index) :
    Slot(inventory, index), player(player), craftMatrix(craftMatrix) {}

bool SlotCrafting::isValid(std::shared_ptr<ItemStack>) {
    return false;
}

void SlotCrafting::onCrafting(std::shared_ptr<ItemStack> stack) {
    stack->onCrafting(player);
}

void SlotCrafting::onCrafting(std::shared_ptr<ItemStack> stack, count_t) {
    onCrafting(stack);
}

void SlotCrafting::onPickupFromSlot(EntityPlayer *player, std::shared_ptr<ItemStack> stack) {
    onCrafting(stack);
    std::vector<std::shared_ptr<ItemStack>> craftResult; // TODO Rechercher dans les recettes
    for (short_t index = 0; index < craftResult.size(); ++index) {
        if (craftMatrix.getStack(index) != nullptr)
            craftMatrix.decrStackSize(index, 1);
        std::shared_ptr<ItemStack> resultStack = craftResult[index];
        if (resultStack != nullptr) {
            if (craftMatrix.getStack(index) == nullptr)
                craftMatrix.setStack(index, resultStack);
            else if (!player->getInventory().addStack(resultStack))
                player->drop(resultStack);
        }
    }
}
