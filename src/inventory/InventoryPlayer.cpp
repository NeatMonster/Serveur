#include "InventoryPlayer.h"

#include "EntityPlayer.h"

InventoryPlayer::InventoryPlayer(EntityPlayer *player) : currentItem(0), player(player) {}

std::shared_ptr<ItemStack> InventoryPlayer::getStack() {
    return stack;
}

std::shared_ptr<ItemStack> InventoryPlayer::getStack(short_t index) {
    if (index >= 36)
        return armor[index - 36];
    else
        return main[index];
}

void InventoryPlayer::setStack(std::shared_ptr<ItemStack> stack) {
    this->stack = stack;
}

void InventoryPlayer::setStack(short_t index, std::shared_ptr<ItemStack> stack) {
    if (index >= 36)
        armor[index - 36] = stack;
    else
        main[index] = stack;
}

int InventoryPlayer::getInventoryStackLimit() {
    return 64;
}

bool InventoryPlayer::addStack(std::shared_ptr<ItemStack> &stack) {
    if (stack == nullptr || stack->getCount() == 0 || stack->getItem() == nullptr)
        return false;
    if (stack->isDamaged()) {
        short_t index = getFirstEmpty();
        if (index >= 0) {
            main[index] = stack->clone();
            stack->setCount(0);
            return true;
        } else if (player->getCapabilities().isCreativeMode) {
            stack->setCount(0);
            return true;
        } else
            return false;
    } else {
        int amount;
        do {
            amount = stack->getCount();
            stack->setCount(storePartialItemStack(stack));
        } while (stack->getCount() > 0 && stack->getCount() < amount);
        if (stack->getCount() == amount && player->getCapabilities().isCreativeMode) {
            stack->setCount(0);
            return true;
        } else
            return stack->getCount() < amount;
    }
}

short_t InventoryPlayer::getFirstEmpty() {
    for (short_t index = 0; index < 36; ++index)
        if (main[index] == nullptr)
            return index;
    return -1;
}

int InventoryPlayer::storeItemStack(std::shared_ptr<ItemStack> stack) {
    for (short_t index = 0; index < 36; ++index)
        if (main[index] != nullptr && main[index]->equals(stack, false, true) && main[index]->isStackable()
            && main[index]->getCount() < main[index]->getItem()->getMaxStackSize()
            && main[index]->getCount() < getInventoryStackLimit())
            return index;
    return -1;
}

int InventoryPlayer::storePartialItemStack(std::shared_ptr<ItemStack> stack) {
    int count = stack->getCount();
    short_t slot = storeItemStack(stack);
    if (slot < 0)
        slot = getFirstEmpty();
    if (slot < 0)
        return count;
    else {
        if (main[slot] == nullptr) {
            main[slot] = std::make_shared<ItemStack>(stack->getItem(), 0, stack->getDamage());
            main[slot]->setTag(stack->getTag());
        }
        int stored = count;
        if (count > main[slot]->getItem()->getMaxStackSize() - main[slot]->getCount())
            stored = main[slot]->getItem()->getMaxStackSize() - main[slot]->getCount();
        if (stored > getInventoryStackLimit() - main[slot]->getCount())
            stored = getInventoryStackLimit() - main[slot]->getCount();
        if (stored == 0)
            return count;
        else {
            count -= stored;
            main[slot]->setCount(main[slot]->getCount() + stored);
            return count;
        }
    }
}
