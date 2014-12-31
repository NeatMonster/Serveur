#include "PacketHandshake.h"

#include "PacketHandler.h"

void PacketHandshake::read(PacketBuffer &buffer) {
    buffer.getVarInt(protocol);
    buffer.getString(serverIP);
    buffer.getUShort(serverPort);
    buffer.getVarInt(nextState);
}

void PacketHandshake::handle(PacketHandler *handler) {
    handler->handleHandshake(this);
}
