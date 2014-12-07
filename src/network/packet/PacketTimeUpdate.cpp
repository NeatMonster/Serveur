#include "PacketTimeUpdate.h"

PacketTimeUpdate::PacketTimeUpdate() : ServerPacket(0x03) {};

void PacketTimeUpdate::write(ByteBuffer &buffer) {
    buffer.putLong(worldAge);
    buffer.putLong(dayTime);
}
