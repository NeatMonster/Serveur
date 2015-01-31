#include "PacketWindowItems.h"

PacketWindowItems::PacketWindowItems() : ServerPacket(0x30) {}

void PacketWindowItems::write(PacketBuffer &buffer) {
    buffer.putUByte(windowId);
    buffer.putShort(stacks.size());
    for (std::shared_ptr<ItemStack> stack : stacks)
        buffer.putItemStack(stack);
}
