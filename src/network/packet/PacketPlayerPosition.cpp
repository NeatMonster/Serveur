#include "PacketPlayerPosition.h"

#include "PacketHandler.h"

PacketPlayerPosition::PacketPlayerPosition() : ClientPacket(0x04) {}

void PacketPlayerPosition::read(ByteBuffer &buffer) {
    buffer.getDouble(x);
    buffer.getDouble(y);
    buffer.getDouble(z);
    buffer.getBool(onGround);
}

void PacketPlayerPosition::handle(PacketHandler *handler) {
    handler->handlePlayerPosition(this);
}
