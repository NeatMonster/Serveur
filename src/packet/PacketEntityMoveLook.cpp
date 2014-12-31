#include "PacketEntityMoveLook.h"

PacketEntityMoveLook::PacketEntityMoveLook() : ServerPacket(0x17) {}

void PacketEntityMoveLook::write(PacketBuffer &buffer) {
    buffer.putVarInt(entityId);
    buffer.putByte(dX);
    buffer.putByte(dY);
    buffer.putByte(dZ);
    buffer.putByte(yaw);
    buffer.putByte(pitch);
    buffer.putBool(onGround);
}
