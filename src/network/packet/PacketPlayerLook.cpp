#include "PacketPlayerLook.h"

#include "PacketHandler.h"

PacketPlayerLook::PacketPlayerLook() : ClientPacket(0x05) {}

void PacketPlayerLook::read(ByteBuffer &buffer) {
    buffer.getFloat(yaw);
    buffer.getFloat(pitch);
    buffer.getBool(onGround);
}

void PacketPlayerLook::handle(PacketHandler *handler) {
    handler->handlePlayerLook(this);
}
