#include "PacketJoinGame.h"

PacketJoinGame::PacketJoinGame() : ServerPacket(0x01) {}

void PacketJoinGame::write(ByteBuffer &buffer) {
    buffer.putInt(entityId);
    buffer.putUByte(gameMode);
    buffer.putByte(dimension);
    buffer.putUByte(difficulty);
    buffer.putUByte(maxPlayers);
    buffer.putString(levelType);
    buffer.putBool(reducedDebugInfo);
}
