#include "ContainerPlayer.h"

#include "Slot.h"
#include "SlotArmor.h"
#include "SlotCrafting.h"

ContainerPlayer::ContainerPlayer(InventoryPlayer &inventory, EntityPlayer *player) : /*player(player),*/ craftMatrix(*this, 2) {
    addSlot(new SlotCrafting(player, craftMatrix, craftResult, 0));
    for (short_t index = 0; index < 4; ++index)
        addSlot(new Slot(craftMatrix, index));
    for (short_t index = 0; index < 4; ++index)
        addSlot(new SlotArmor(craftMatrix, 39 - index));
    for (short_t index = 9; index < 36; ++index)
        addSlot(new Slot(inventory, index));
    for (short_t index = 0; index < 9; ++index)
        addSlot(new Slot(inventory, index));
    onCraftMatrixChanged(craftMatrix);
}

bool ContainerPlayer::canTakeFromSlot(std::shared_ptr<ItemStack> stack, Slot *slot) {
    return &slot->inventory != &craftResult && Container::canTakeFromSlot(stack, slot);
}

std::shared_ptr<ItemStack> ContainerPlayer::transferStackInSlot(EntityPlayer *player, short_t index) {
    std::shared_ptr<ItemStack> stack = nullptr;
    Slot *slot = getSlot(index);
    if (slot != nullptr && slot->hasStack()) {
        std::shared_ptr<ItemStack> slotStack = slot->getStack();
        stack = slotStack->clone();
        if (index == 0) {
            if (!mergeItemStack(slotStack, 9, 45, true))
                return nullptr;
            slot->onSlotChange(slotStack, stack);
        } else if (index >= 1 && index < 5) {
            if (!mergeItemStack(slotStack, 9, 45, false))
                return nullptr;
        } else if (index >= 5 && index < 9) {
            if (!mergeItemStack(slotStack, 9, 45, false))
                return nullptr;
        }
        // TODO Ajouter un cas pour les armures
        else if (index >= 9 && index < 36) {
            if (!mergeItemStack(slotStack, 36, 45, false))
                return nullptr;
        } else if (!mergeItemStack(slotStack, 9, 45, false))
            return nullptr;
        if (slotStack->getCount() == 0)
            slot->putStack(nullptr);
        if (slotStack->getCount() == stack->getCount())
            return nullptr;
        slot->onPickupFromSlot(player, slotStack);
    }
    return stack;
}
