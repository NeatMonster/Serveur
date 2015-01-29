#include "PacketSetSlot.h"

PacketSetSlot::PacketSetSlot() : ServerPacket(0x2f) {}

void PacketSetSlot::write(PacketBuffer &buffer) {
    buffer.putByte(windowId);
    buffer.putShort(slot);
    buffer.putItemStack(stack);
}
