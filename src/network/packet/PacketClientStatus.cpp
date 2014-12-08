#include "PacketClientStatus.h"

void PacketClientStatus::read(ByteBuffer &buffer) {
    buffer.getVarInt(actionId);
}
