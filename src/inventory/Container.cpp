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
                                 std::shared_ptr<ItemStack> &dragStack, int slotStackSize) {
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
                        slot->setStack(stack);
                    }
                cursor->setCount(cursorSize);
                if (cursor->getCount())
                    cursor = nullptr;
                inventory.setCursor(cursor);
            }
            resetDrag();
        } else
            resetDrag();
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
    getSlot(index)->setStack(stack);
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
