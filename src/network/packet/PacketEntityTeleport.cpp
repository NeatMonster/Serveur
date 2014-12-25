#include "PacketEntityTeleport.h"

PacketEntityTeleport::PacketEntityTeleport() : ServerPacket(0x18) {}

void PacketEntityTeleport::write(PacketBuffer &buffer) {
    buffer.putVarInt(entityId);
    buffer.putInt(x);
    buffer.putInt(y);
    buffer.putInt(z);
    buffer.putByte(yaw);
    buffer.putByte(pitch);
    buffer.putBool(onGround);
}
