#include "PacketEntityLook.h"

PacketEntityLook::PacketEntityLook() : ServerPacket(0x16) {}

void PacketEntityLook::write(PacketBuffer &buffer) {
    buffer.putVarInt(entityId);
    buffer.putByte(yaw);
    buffer.putByte(pitch);
    buffer.putBool(onGround);
}
