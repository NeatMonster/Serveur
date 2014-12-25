#include "PacketEntityMove.h"

PacketEntityMove::PacketEntityMove() : ServerPacket(0x15) {}

void PacketEntityMove::write(PacketBuffer &buffer) {
    buffer.putVarInt(entityId);
    buffer.putByte(dX);
    buffer.putByte(dY);
    buffer.putByte(dZ);
    buffer.putBool(onGround);
}
