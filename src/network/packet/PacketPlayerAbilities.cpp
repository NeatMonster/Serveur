#include "PacketPlayerAbilities.h"

PacketPlayerAbilities::PacketPlayerAbilities() : ServerPacket(0x39) {}

void PacketPlayerAbilities::read(ByteBuffer &buffer) {
    byte_t flags;
    buffer.getByte(flags);
    godMode |= flags << 3;
    canFly |= flags << 2;
    isFlying |= flags << 1;
    creativeMode |= flags;
    buffer.getFloat(flyingSpeed);
    buffer.getFloat(walkingSpeed);
}

void PacketPlayerAbilities::write(ByteBuffer &buffer) {
    byte_t flags = 0;
    flags |= godMode << 3;
    flags |= canFly << 2;
    flags |= isFlying << 1;
    flags |= creativeMode;
    buffer.putByte(flags);
    buffer.putFloat(flyingSpeed);
    buffer.putFloat(walkingSpeed);
}
