#include "PacketPlayerPositionLook.h"

#include "PacketHandler.h"

PacketPlayerPositionLook::PacketPlayerPositionLook() : ServerPacket(0x08) {};

void PacketPlayerPositionLook::read(PacketBuffer &buffer) {
    buffer.getDouble(x);
    buffer.getDouble(y);
    buffer.getDouble(z);
    buffer.getFloat(yaw);
    buffer.getFloat(pitch);
    buffer.getBool(onGround);
}

void PacketPlayerPositionLook::write(PacketBuffer &buffer) {
    buffer.putDouble(x);
    buffer.putDouble(y);
    buffer.putDouble(z);
    buffer.putFloat(yaw);
    buffer.putFloat(pitch);
    buffer.putByte(flags);
}

void PacketPlayerPositionLook::handle(PacketHandler *handler) {
    handler->handlePlayerPositionLook(this);
}
