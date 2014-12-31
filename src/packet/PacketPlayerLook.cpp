#include "PacketPlayerLook.h"

#include "PacketHandler.h"

void PacketPlayerLook::read(PacketBuffer &buffer) {
    buffer.getFloat(yaw);
    buffer.getFloat(pitch);
    buffer.getBool(onGround);
}

void PacketPlayerLook::handle(PacketHandler *handler) {
    handler->handlePlayerLook(this);
}
