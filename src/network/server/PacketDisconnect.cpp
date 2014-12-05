#include "PacketDisconnect.h"

#include "PlayerConnection.h"

PacketDisconnect::PacketDisconnect() : ServerPacket(0x00) {}

void PacketDisconnect::write(ByteBuffer &buffer) {
    buffer.putString(reason);
}
