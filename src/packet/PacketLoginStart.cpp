#include "PacketLoginStart.h"

#include "PacketHandler.h"

void PacketLoginStart::read(PacketBuffer &buffer) {
    buffer.getString(name);
}

void PacketLoginStart::handle(PacketHandler *handler) {
    handler->handleLoginStart(this);
}
