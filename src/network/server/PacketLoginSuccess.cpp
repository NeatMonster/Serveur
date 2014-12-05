#include "PacketLoginSuccess.h"

PacketLoginSuccess::PacketLoginSuccess() : ServerPacket(0x02) {}

void PacketLoginSuccess::write(ByteBuffer &buffer) {
    buffer.putString(uuid);
    buffer.putString(username);
}
