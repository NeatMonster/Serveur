#include "PacketClientStatus.h"

#include "PacketClientStatus.h"

PacketClientStatus::PacketClientStatus() : ClientPacket(0x16) {}

void PacketClientStatus::read(ByteBuffer &buffer) {
    buffer.getVarInt(actionId);
}
