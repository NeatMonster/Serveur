#include "PacketHeldItemChange.h"

void PacketHeldItemChange::read(ByteBuffer &buffer) {
    buffer.getShort(slot);
}
