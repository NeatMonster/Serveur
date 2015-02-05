#include "Container.h"

#include "InventoryPlayer.h"
#include "MathUtils.h"
#include "PacketSetSlot.h"
#include "PacketWindowItems.h"
#include "SlotCrafting.h"

bool Container::canAddItemToSlot(Slot* slot, std::shared_ptr<ItemStack> stack) {
    return slot == nullptr || !slot->hasStack() || (stack->equals(slot->getStack(), false, true)
        && slot->getStack()->getCount() < stack->getMaxStackSize());
}

void Container::computeStackSize(std::set<Slot*> dragSlots, ubyte_t dragMode,
                                 std::shared_ptr<ItemStack> dragStack, int slotStackSize) {
    if (dragMode == 0)
        dragStack->setCount(MathUtils::floor_f((float_t) dragStack->getCount() / (float_t) dragSlots.size()));
    else if (dragMode == 1)
        dragStack->setCount(1);
    else if (dragMode == 2)
        dragStack->setCount(dragStack->getMaxStackSize());
    dragStack->setCount(dragStack->getCount() + slotStackSize);
}

Container::Container() : windowId(0) {}

Container::~Container() {
    for (Slot *slot : slots)
        delete slot;
}

std::shared_ptr<ItemStack> Container::slotClick(short_t slotId, ubyte_t button, ubyte_t mode, EntityPlayer *player) {
    std::shared_ptr<ItemStack> result = nullptr;
    InventoryPlayer &inventory = player->getInventory();
    if (mode == 5) {
        ubyte_t oldDragEvent = dragEvent;
        dragEvent = button & 3;
        if ((oldDragEvent != 1 || dragEvent != 2) && oldDragEvent != dragEvent)
            resetDrag();
        else if (inventory.getCursor() == nullptr)
            resetDrag();
        else if (dragEvent == 0) {
            dragMode = button >> 2 & 3;
            if (dragMode == 0 || dragMode == 1 || (dragMode == 2 && player->getCapabilities().isCreativeMode)) {
                dragEvent = 1;
                dragSlots.clear();
            } else
                resetDrag();
        } else if (dragEvent == 1) {
            Slot *slot = getSlot(slotId);
            if (slot != nullptr && canAddItemToSlot(slot, inventory.getCursor()) && slot->isValid(inventory.getCursor())
                && inventory.getCursor()->getCount() > dragSlots.size())
                dragSlots.insert(slot);
        } else if (dragEvent == 2) {
            if (!dragSlots.empty()) {
                std::shared_ptr<ItemStack> cursor = inventory.getCursor();
                int cursorSize = cursor->getCount();
                for (Slot *slot : dragSlots)
                    if (slot != nullptr && canAddItemToSlot(slot, inventory.getCursor()) && slot->isValid(inventory.getCursor())
                        && inventory.getCursor()->getCount() > dragSlots.size()) {
                        std::shared_ptr<ItemStack> stack = cursor->clone();
                        int slotStackSize = slot->hasStack() ? slot->getStack()->getCount() : 0;
                        computeStackSize(dragSlots, dragMode, stack, slotStackSize);
                        if (stack->getCount() > stack->getMaxStackSize())
                            stack->setCount(stack->getMaxStackSize());
                        if (stack->getCount() > slot->getSlotMaxSize(stack))
                            stack->setCount(slot->getSlotMaxSize(stack));
                        cursorSize -= stack->getCount() - slotStackSize;
                        slot->putStack(stack);
                    }
                cursor->setCount(cursorSize);
                if (cursor->getCount())
                    cursor = nullptr;
                inventory.setCursor(cursor);
            }
            resetDrag();
        } else
            resetDrag();
    } else if (dragEvent != 0)
        resetDrag();
    else {
        if ((mode == 0 || mode == 1) && (button == 0 || button == 1)) {
            if (slotId == -999) {
                if (inventory.getCursor() != nullptr) {
                    if (button == 0) {
                        player->drop(inventory.getCursor());
                        inventory.setCursor(nullptr);
                    } else {
                        player->drop(inventory.getCursor()->splitStack(1));
                        if (inventory.getCursor()->getCount() == 0)
                            inventory.setCursor(nullptr);
                    }
                }
            } else if (mode == 1) {
                if (slotId < 0)
                    return nullptr;
                Slot *slot = getSlot(slotId);
                if (slot != nullptr && slot->canTakeStack(player)) {
                    std::shared_ptr<ItemStack> stack = transferStackInSlot(player, slotId);
                    if (stack != nullptr) {
                        result = stack->clone();
                        if (slot->getStack() != nullptr && slot->getStack()->getItem() == stack->getItem())
                            slotClick(slotId, button, 1, player);
                    }
                }
            } else {
                if (slotId < 0)
                    return nullptr;
                Slot *slot = getSlot(slotId);
                if (slot != nullptr) {
                    std::shared_ptr<ItemStack> stack = slot->getStack();
                    std::shared_ptr<ItemStack> cursor = inventory.getCursor();
                    if (stack != nullptr)
                        result = stack->clone();
                    if (stack == nullptr) {
                        if (cursor != nullptr && slot->isValid(cursor)) {
                            int count = button == 0 ? cursor->getCount() : 1;
                            if (count > slot->getSlotMaxSize(cursor))
                                count = slot->getSlotMaxSize(cursor);
                            if (cursor->getCount() >= count)
                                slot->putStack(cursor->splitStack(count));
                            if (cursor->getCount() == 0)
                                inventory.setCursor(nullptr);
                        }
                    } else if (slot->canTakeStack(player)) {
                        if (cursor == nullptr) {
                            int count = button == 0 ? stack->getCount() : (stack->getCount() + 1) / 2;
                            inventory.setCursor(slot->decrStackSize(count));
                            if (stack->getCount() == 0)
                                slot->putStack(nullptr);
                            slot->onPickupFromSlot(player, inventory.getCursor());
                        } else if (slot->isValid(cursor)) {
                            if (stack->equals(cursor, false, true)) {
                                int count = button == 0 ? cursor->getCount() : 1;
                                if (count > slot->getSlotMaxSize(cursor) - stack->getCount())
                                    count = slot->getSlotMaxSize(cursor) - stack->getCount();
                                if (count > cursor->getMaxStackSize() - stack->getCount())
                                    count = cursor->getMaxStackSize() - stack->getCount();
                                cursor->splitStack(count);
                                if (cursor->getCount() == 0)
                                    inventory.setCursor(cursor);
                                stack->setCount(stack->getCount() + count);
                            } else if (cursor->getCount() <= slot->getSlotMaxSize(cursor)) {
                                slot->putStack(cursor);
                                inventory.setCursor(stack);
                            }
                        } else if (stack->equals(cursor, false, true) && cursor->getMaxStackSize() > 1) {
                            int count = stack->getCount();
                            if (count > 0 && count + cursor->getCount() <= cursor->getMaxStackSize()) {
                                cursor->setCount(cursor->getCount() + count);
                                stack = slot->decrStackSize(count);
                                if (stack->getCount() == 0)
                                    slot->putStack(nullptr);
                                slot->onPickupFromSlot(player, inventory.getCursor());
                            }
                        }
                    }
                }
            }
        }
    }
    // TODO Implémenter les autres modes
}

void Container::detectAndSendChanges() {
    for (int slotId = 0; slotId < slots.size(); ++slotId) {
        std::shared_ptr<ItemStack> stack = slots[slotId]->getStack();
        if ((stacks[slotId] == nullptr && stack != nullptr) || (stacks[slotId] != nullptr && !stacks[slotId]->equals(stack, true, true))) {
            stacks[slotId] = stack == nullptr ? nullptr : stack->clone();
            if (dynamic_cast<SlotCrafting*>(getSlot(slotId)) == nullptr) {
                std::shared_ptr<PacketSetSlot> packet = std::make_shared<PacketSetSlot>();
                packet->windowId = windowId;
                packet->slot = slotId;
                packet->stack = stack->clone();
                for (EntityPlayer *watcher : watchers)
                    watcher->sendPacket(packet);
            }
        }
    }
}

void Container::addSlot(Slot *slot) {
    slot->slotNumber = slots.size();
    slots.push_back(slot);
    stacks.push_back(nullptr);
}

bool Container::mergeItemStack(std::shared_ptr<ItemStack> stack, short_t startIndex, short_t endIndex, bool useEndIndex) {
    bool slotChanged = false;
    int index = startIndex;
    if (useEndIndex)
        index = endIndex - 1;
    if (stack->isStackable()) {
        while (stack->getCount() > 0 && ((!useEndIndex && index < endIndex) || (useEndIndex && index >= startIndex))) {
            std::shared_ptr<ItemStack> slotStack = getSlot(index)->getStack();
            if (slotStack != nullptr && slotStack->equals(stack, false, true)) {
                int count = slotStack->getCount() + stack->getCount();
                if (count <= stack->getMaxStackSize()) {
                    stack->setCount(0);
                    slotStack->setCount(count);
                    slotChanged = true;
                } else if (slotStack->getCount() < stack->getMaxStackSize()) {
                    stack->setCount(stack->getCount() - stack->getMaxStackSize() + slotStack->getCount());
                    slotStack->setCount(stack->getMaxStackSize());
                    slotChanged = true;
                }
            }
            if (useEndIndex)
                --index;
            else
                ++index;
        }
    }
    if (stack->getCount() > 0) {
        if (useEndIndex)
            index = endIndex - 1;
        else
            index = startIndex;
        while ((!useEndIndex && index < endIndex) || (useEndIndex && index >= startIndex)) {
            Slot *slot = getSlot(index);
            std::shared_ptr<ItemStack> slotStack = slot->getStack();
            if (slotStack == nullptr) {
                slot->putStack(stack->clone());
                stack->setCount(0);
                slotChanged = true;
                break;
            }
            if (useEndIndex)
                --index;
            else
                ++index;
        }
    }
    return slotChanged;
}

void Container::resetDrag() {
    dragEvent = 0;
    dragSlots.clear();
}

Slot *Container::getSlot(short_t index) {
    if (index < slots.size())
        return slots[index];
    return nullptr;
}

std::vector<std::shared_ptr<ItemStack>> Container::getInventory() {
    std::vector<std::shared_ptr<ItemStack>> inventory;
    for (Slot *slot : slots)
        inventory.push_back(slot->getStack());
    return inventory;
}

void Container::putStack(short_t index, std::shared_ptr<ItemStack> stack) {
    getSlot(index)->putStack(stack);
}

std::shared_ptr<ItemStack> Container::transferStackInSlot(EntityPlayer*, short_t index) {
    Slot *slot = getSlot(index);
    return slot != nullptr ? slot->getStack() : nullptr;
}

void Container::onCraftGuiOpened(EntityPlayer *player) {
    watchers.insert(player);
    std::shared_ptr<PacketWindowItems> itemsPacket = std::make_shared<PacketWindowItems>();
    itemsPacket->windowId = windowId;
    itemsPacket->stacks = getInventory();
    player->sendPacket(itemsPacket);
    std::shared_ptr<PacketSetSlot> slotPacket = std::make_shared<PacketSetSlot>();
    slotPacket->windowId = -1;
    slotPacket->slot = -1;
    slotPacket->stack = player->getInventory().getCursor();
    player->sendPacket(slotPacket);
    detectAndSendChanges();
}

void Container::onCraftMatrixChanged(Inventory&) {}
