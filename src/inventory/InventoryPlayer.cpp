#include "InventoryPlayer.h"

#include "EntityPlayer.h"

InventoryPlayer::InventoryPlayer(EntityPlayer *player) : player(player) {}

bool InventoryPlayer::addItemStack(std::shared_ptr<ItemStack> stack) {
    if (stack == nullptr || stack->getCount() == 0 || stack->getItem() == nullptr)
        return false;
    if (stack->getDamage() > 0) {
        int firstEmpty = getFirstEmpty();
        if (firstEmpty >= 0)
            main[firstEmpty] = stack->clone();
        else if (player->getGameMode() == EntityPlayer::GameMode::CREATIVE)
            stack->setCount(0);
        else
            return false;
        stack->setCount(0);
        return true;
    } else {
        int amount;
        do {
            amount = stack->getCount();
            stack->setCount(storePartialItemStack(stack));
        } while (stack->getCount() > 0 && stack->getCount() < amount);
        if (stack->getCount() == amount && player->getGameMode() == EntityPlayer::GameMode::CREATIVE) {
            stack->setCount(0);
            return true;
        } else
            return stack->getCount() < amount;
    }
}

std::shared_ptr<ItemStack> InventoryPlayer::getItemStack(int slot) {
    if (slot >= 9 && slot <= 44)
        return main[slot - 9];
    return nullptr;
}

void InventoryPlayer::putItemStack(int slot, std::shared_ptr<ItemStack> stack) {
    if (slot >= 9 && slot <= 44)
        main[slot - 9] = stack;
}

int InventoryPlayer::getFirstEmpty() {
    for (int slot = 0; slot < 36; slot++)
        if (main[slot] != nullptr)
            return slot;
    return -1;
}

int InventoryPlayer::storeItemStack(std::shared_ptr<ItemStack> stack) {
    for (int slot = 0; slot < 36; slot++)
        if (main[slot] != nullptr && main[slot]->isStackable() && main[slot]->getItem() == stack->getItem()
                && main[slot]->getCount() < main[slot]->getItem()->getMaxStackSize() && main[slot]->getDamage() == stack->getDamage()
                && ((main[slot]->getTag() == nullptr && stack->getTag() == nullptr) || main[slot]->getTag()->equals(stack->getTag())))
            return slot;
    return -1;
}

int InventoryPlayer::storePartialItemStack(std::shared_ptr<ItemStack> stack) {
    int count = stack->getCount();
    int slot = storeItemStack(stack);
    if (slot < 0)
        slot = getFirstEmpty();
    if (slot < 0)
        return count;
    else {
        if (main[slot] == nullptr) {
            main[slot] = std::make_shared<ItemStack>(stack->getItem(), 0, stack->getDamage());
            if (stack->getTag() != nullptr)
                main[slot]->setTag(stack->getTag());
        }
        int stored = count;
        if (count > main[slot]->getItem()->getMaxStackSize() - main[slot]->getCount())
            stored = main[slot]->getItem()->getMaxStackSize() - main[slot]->getCount();
        if (stored == 0)
            return count;
        else {
            count -= stored;
            main[slot]->setCount(main[slot]->getCount() + stored);
            return count;
        }
    }
}
