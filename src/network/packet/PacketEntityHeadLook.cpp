#include "PacketEntityHeadLook.h"

PacketEntityHeadLook::PacketEntityHeadLook() : ServerPacket(0x19) {}

void PacketEntityHeadLook::write(PacketBuffer &buffer) {
    buffer.putVarInt(entityId);
    buffer.putByte(headYaw);
}
