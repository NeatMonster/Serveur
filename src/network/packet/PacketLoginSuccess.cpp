#include "PacketLoginSuccess.h"

PacketLoginSuccess::PacketLoginSuccess(string_t uuid, string_t name) : ServerPacket(0x02) {
    this->uuid = uuid;
    this->name = name;
}

void PacketLoginSuccess::write(ByteBuffer &buffer) {
    buffer.putString(uuid);
    buffer.putString(name);
}
