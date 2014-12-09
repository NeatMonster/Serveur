#include "PacketPlayerDigging.h"

void PacketPlayerDigging::read(ByteBuffer &buffer) {
    buffer.getVarInt(status);
    long_t location;
    buffer.getLong(location);
    this->location = position_t(location);
    buffer.getUByte(face);
}
