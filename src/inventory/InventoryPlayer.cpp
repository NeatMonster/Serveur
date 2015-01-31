#include "InventoryPlayer.h"

#include "EntityPlayer.h"
#include "PacketSetSlot.h"
#include "PacketWindowItems.h"

InventoryPlayer::InventoryPlayer(EntityPlayer *player) : player(player) {}

bool InventoryPlayer::addItemStack(std::shared_ptr<ItemStack> stack) {
    if (stack == nullptr || stack->getCount() == 0 || stack->getItem() == nullptr)
        return false;
    if (stack->getDamage() > 0) {
        int firstEmpty = getFirstEmpty();
        if (firstEmpty >= 0)
            putItemStack(firstEmpty, stack->clone());
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
    return slots[slot];
}

void InventoryPlayer::putItemStack(int slot, std::shared_ptr<ItemStack> stack) {
    slots[slot] = stack;
    std::shared_ptr<PacketSetSlot> packet = std::make_shared<PacketSetSlot>();
    packet->windowId = 0;
    packet->slot = slot;
    packet->stack = stack;
    player->sendPacket(packet);
}

void InventoryPlayer::sendContent() {
    std::shared_ptr<PacketWindowItems> packet = std::make_shared<PacketWindowItems>();
    packet->windowId = 0;
    for (std::shared_ptr<ItemStack> slot : slots)
        packet->stacks.push_back(slot);
    player->sendPacket(packet);
}

int InventoryPlayer::getFirstEmpty() {
    for (int y = 4; y > 0; y--)
        for (int x = 0; x < 9; x++)
            if (slots[y * 9 + x] == nullptr)
                return y * 9 + x;
    return -1;
}

int InventoryPlayer::storeItemStack(std::shared_ptr<ItemStack> stack) {
    for (int y = 4; y > 0; y--)
        for (int x = 0; x < 9; x++) {
            std::shared_ptr<ItemStack> slotStack = slots[y * 9 + x];
            if (slotStack != nullptr && slotStack->isStackable() && slotStack->getItem() == stack->getItem()
                    && slotStack->getCount() < slotStack->getItem()->getMaxStackSize() && slotStack->getDamage() == stack->getDamage()
                    && ((slotStack->getTag() == nullptr && stack->getTag() == nullptr) || slotStack->getTag()->equals(stack->getTag())))
                return y * 9 + x;
        }
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
        if (slots[slot] == nullptr) {
            std::shared_ptr<ItemStack> slotStack = std::make_shared<ItemStack>(stack->getItem(), 0, stack->getDamage());
            if (stack->getTag() != nullptr)
                slotStack->setTag(stack->getTag());
            putItemStack(slot, slotStack);
        }
        int stored = count;
        if (count > slots[slot]->getItem()->getMaxStackSize() - slots[slot]->getCount())
            stored = slots[slot]->getItem()->getMaxStackSize() - slots[slot]->getCount();
        if (stored == 0)
            return count;
        else {
            count -= stored;
            slots[slot]->setCount(slots[slot]->getCount() + stored);
            putItemStack(slot, slots[slot]);
            return count;
        }
    }
}
