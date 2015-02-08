#include "PacketHeldItemChange.h"

#include "PacketHandler.h"

void PacketHeldItemChange::read(PacketBuffer &buffer) {
    buffer.getShort(slot);
}

void PacketHeldItemChange::handle(PacketHandler *handler) {
    handler->handleHeldItemChange(this);
}
