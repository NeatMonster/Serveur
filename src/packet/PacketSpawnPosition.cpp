#include "PacketSpawnPosition.h"

PacketSpawnPosition::PacketSpawnPosition(int_t x, int_t y, int_t z) : ServerPacket(0x05) {
    this->location = Position(x, y, z);
}

void PacketSpawnPosition::write(PacketBuffer &buffer) {
    buffer.putLong(location.l);
}
