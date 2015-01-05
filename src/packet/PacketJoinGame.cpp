#include "PacketJoinGame.h"

PacketJoinGame::PacketJoinGame() : ServerPacket(0x01) {}

void PacketJoinGame::write(PacketBuffer &buffer) {
    buffer.putInt(entityId);
    buffer.putUByte(gamemode);
    buffer.putByte(dimension);
    buffer.putUByte(difficulty);
    buffer.putUByte(maxPlayers);
    buffer.putString(levelType);
    buffer.putBool(reducedDebugInfo);
}
