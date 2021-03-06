#include "InventoryPlayer.h"

#include "EntityPlayer.h"

InventoryPlayer::InventoryPlayer(EntityPlayer *player) : /*currentItem(0),*/ player(player) {}

std::shared_ptr<ItemStack> InventoryPlayer::getCursor() {
    return cursor;
}

void InventoryPlayer::setCursor(std::shared_ptr<ItemStack> cursor) {
    this->cursor = cursor;
}

std::shared_ptr<ItemStack> InventoryPlayer::getStack(short_t index) {
    if (index >= 36)
        return armor[index - 36];
    else
        return main[index];
}

void InventoryPlayer::setStack(short_t index, std::shared_ptr<ItemStack> stack) {
    if (index >= 36)
        armor[index - 36] = stack;
    else
        main[index] = stack;
}

short_t InventoryPlayer::getCurrentItem() {
    return currentItem;
}

void InventoryPlayer::setCurrentItem(short_t currentItem) {
    this->currentItem = currentItem;
}

std::shared_ptr<ItemStack> InventoryPlayer::decrStackSize(short_t index, count_t count) {
    std::shared_ptr<ItemStack> *inv = main;
    if (index >= 36) {
        inv = armor;
        index -= 36;
    }
    if (inv[index] != nullptr) {
        if (inv[index]->getCount() <= count) {
            std::shared_ptr<ItemStack> stack = inv[index];
            inv[index] = nullptr;
            return stack;
        } else {
            std::shared_ptr<ItemStack> stack = inv[index]->splitStack(count);
            if (inv[index]->getCount() == 0)
                inv[index] = nullptr;
            return stack;
        }
    } else
        return nullptr;
}

short_t InventoryPlayer::getFirstEmpty() {
    for (short_t index = 0; index < 36; ++index)
        if (main[index] == nullptr)
            return index;
    return -1;
}

count_t InventoryPlayer::getInventoryStackLimit() {
    return 64;
}

bool InventoryPlayer::addStack(std::shared_ptr<ItemStack> stack) {
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

int InventoryPlayer::storeItemStack(std::shared_ptr<ItemStack> stack) {
    for (short_t index = 0; index < 36; ++index)
        if (main[index] != nullptr && main[index]->equals(stack, false) && main[index]->isStackable()
            && main[index]->getCount() < main[index]->getMaxStackSize()
            && main[index]->getCount() < getInventoryStackLimit())
            return index;
    return -1;
}

int InventoryPlayer::storePartialItemStack(std::shared_ptr<ItemStack> stack) {
    count_t count = stack->getCount();
    short_t slot = storeItemStack(stack);
    if (slot < 0)
        slot = getFirstEmpty();
    if (slot < 0)
        return count;
    else {
        if (main[slot] == nullptr) {
            main[slot] = std::make_shared<ItemStack>(stack->getItem(), 0, stack->getDamage());
            if (stack->hasTag())
                main[slot]->setTag(std::dynamic_pointer_cast<NBTTagCompound>(stack->getTag()->clone()));
        }
        count_t stored = count;
        if (count > main[slot]->getMaxStackSize() - main[slot]->getCount())
            stored = main[slot]->getMaxStackSize() - main[slot]->getCount();
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
