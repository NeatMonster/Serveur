#include "PacketDisconnect.h"

#include "PlayerConnection.h"

PacketDisconnect::PacketDisconnect(bool auth, string_t reason) : ServerPacket(auth ? 0x40 : 0x00) {
    this->reason = reason;
}

void PacketDisconnect::write(ByteBuffer &buffer) {
    buffer.putString(reason);
}
