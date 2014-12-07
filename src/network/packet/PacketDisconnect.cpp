#include "PacketDisconnect.h"

#include "PlayerConnection.h"

PacketDisconnect::PacketDisconnect(string_t reason) : ServerPacket(0x00) {
    this->reason = reason;
}

void PacketDisconnect::write(ByteBuffer &buffer) {
    buffer.putString(reason);
}
