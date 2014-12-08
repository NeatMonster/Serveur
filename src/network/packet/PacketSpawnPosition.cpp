#include "PacketSpawnPosition.h"

PacketSpawnPosition::PacketSpawnPosition(int_t x, int_t y, int_t z) : ServerPacket(0x05) {
    this->location = position_t(x, y, z);
}

void PacketSpawnPosition::write(ByteBuffer &buffer) {
    buffer.putLong(location.pos);
}
