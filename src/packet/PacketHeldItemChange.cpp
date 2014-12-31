#include "PacketHeldItemChange.h"

void PacketHeldItemChange::read(PacketBuffer &buffer) {
    buffer.getShort(slot);
}
