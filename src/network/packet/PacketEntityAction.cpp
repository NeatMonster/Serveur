#include "PacketEntityAction.h"

void PacketEntityAction::read(PacketBuffer &buffer) {
    buffer.getVarInt(entityId);
    buffer.getVarInt(actionId);
    buffer.getVarInt(jumpBoost);
}
