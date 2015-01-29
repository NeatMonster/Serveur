#include "PacketChangeGameState.h"

PacketChangeGameState::PacketChangeGameState() : ServerPacket(0x2b) {}

void PacketChangeGameState::write(PacketBuffer &buffer) {
    buffer.putUByte(reason);
    buffer.putFloat(value);
}
