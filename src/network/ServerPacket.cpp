#include "ServerPacket.h"

ServerPacket::ServerPacket(varint_t packetId) : packetId(packetId) {}

ServerPacket::~ServerPacket() {}

varint_t ServerPacket::getPacketId() {
    return packetId;
}
