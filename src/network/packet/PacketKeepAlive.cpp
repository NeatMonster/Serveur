#include "PacketKeepAlive.h"

#include "PacketHandler.h"

PacketKeepAlive::PacketKeepAlive() : ServerPacket(0x00) {};

PacketKeepAlive::PacketKeepAlive(varint_t keepAliveId) : PacketKeepAlive() {
    this->keepAliveId = keepAliveId;
}

void PacketKeepAlive::read(PacketBuffer &buffer) {
    buffer.getVarInt(keepAliveId);
}

void PacketKeepAlive::write(PacketBuffer &buffer) {
    buffer.putVarInt(keepAliveId);
}

void PacketKeepAlive::handle(PacketHandler *handler) {
    handler->handleKeepAlive(this);
}
