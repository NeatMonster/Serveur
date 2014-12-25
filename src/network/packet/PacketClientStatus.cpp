#include "PacketClientStatus.h"

void PacketClientStatus::read(PacketBuffer &buffer) {
    buffer.getVarInt(actionId);
}
