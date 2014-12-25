#include "PacketPlayer.h"

#include "PacketHandler.h"

void PacketPlayer::read(PacketBuffer &buffer) {
    buffer.getBool(onGround);
}

void PacketPlayer::handle(PacketHandler *handler) {
    handler->handlePlayer(this);
}
