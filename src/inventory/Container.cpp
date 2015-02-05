#include "Container.h"

#include "PacketSetSlot.h"
#include "PacketWindowItems.h"
#include "SlotCrafting.h"

Container::Container() : windowId(0) {}

Container::~Container() {
    for (Slot *slot : slots)
        delete slot;
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

Slot *Container::getSlot(short_t index) {
    return slots[index];
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
    slotPacket->stack = player->getInventory().getStack();
    player->sendPacket(slotPacket);
    detectAndSendChanges();
}

void Container::onCraftMatrixChanged(Inventory&) {}
