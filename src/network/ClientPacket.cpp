#include "ClientPacket.h"

ClientPacket::ClientPacket(varint_t packetId) : Packet(packetId) {}

ClientPacket::~ClientPacket() {}

void ClientPacket::setLength(varint_t packetLength) {
    this->packetLength = packetLength;
}
