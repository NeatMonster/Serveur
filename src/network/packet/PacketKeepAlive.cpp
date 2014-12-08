#include "PacketKeepAlive.h"

#include "PacketHandler.h"

PacketKeepAlive::PacketKeepAlive() : ClientPacket(0x00),ServerPacket(0x00) {};

PacketKeepAlive::PacketKeepAlive(varint_t keepAliveId) : PacketKeepAlive() {
    this->keepAliveId = keepAliveId;
}

void PacketKeepAlive::read(ByteBuffer &buffer) {
    buffer.getVarInt(keepAliveId);
}

void PacketKeepAlive::write(ByteBuffer &buffer) {
    buffer.putVarInt(keepAliveId);
}

void PacketKeepAlive::handle(PacketHandler *handler) {
    handler->handleKeepAlive(this);
}
