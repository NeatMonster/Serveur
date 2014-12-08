#include "PacketEntityAction.h"

void PacketEntityAction::read(ByteBuffer &buffer) {
    buffer.getVarInt(entityId);
    buffer.getVarInt(actionId);
    buffer.getVarInt(jumpBoost);
}
