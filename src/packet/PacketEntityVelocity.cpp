#include "PacketEntityVelocity.h"

PacketEntityVelocity::PacketEntityVelocity() : ServerPacket(0x12) {}

void PacketEntityVelocity::write(PacketBuffer &buffer) {
    buffer.putVarInt(entityId);
    buffer.putShort(velocityX);
    buffer.putShort(velocityY);
    buffer.putShort(velocityZ);
}
