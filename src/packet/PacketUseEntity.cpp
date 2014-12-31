#include "PacketUseEntity.h"

void PacketUseEntity::read(PacketBuffer &buffer) {
    buffer.getVarInt(target);
    buffer.getVarInt(type);
    if (type == 2) {
        buffer.getFloat(targetX);
        buffer.getFloat(targetY);
        buffer.getFloat(targetZ);
    }
}
