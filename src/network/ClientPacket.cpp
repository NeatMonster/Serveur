#include "ClientPacket.h"

ClientPacket::~ClientPacket() {}

void ClientPacket::handle(PacketHandler*) {}

void ClientPacket::setLength(varint_t packetLength) {
    this->packetLength = packetLength;
}
