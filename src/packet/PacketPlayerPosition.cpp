#include "PacketPlayerPosition.h"

#include "PacketHandler.h"

void PacketPlayerPosition::read(PacketBuffer &buffer) {
    buffer.getDouble(x);
    buffer.getDouble(y);
    buffer.getDouble(z);
    buffer.getBool(onGround);
}

void PacketPlayerPosition::handle(PacketHandler *handler) {
    handler->handlePlayerPosition(this);
}
