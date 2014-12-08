#include "PacketPlayer.h"

#include "PacketHandler.h"

void PacketPlayer::read(ByteBuffer &buffer) {
    buffer.getBool(onGround);
}

void PacketPlayer::handle(PacketHandler *handler) {
    handler->handlePlayer(this);
}
