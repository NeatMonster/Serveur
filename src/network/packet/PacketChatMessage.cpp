#include "PacketChatMessage.h"

PacketChatMessage::PacketChatMessage() : ClientPacket(0x02), ServerPacket(0x02) {};

void PacketChatMessage::write(ByteBuffer &buffer) {
    buffer.putString(jsonData);
    buffer.putByte(position);
}

void PacketChatMessage::read(ByteBuffer &buffer) {
    buffer.getString(jsonData);
}

void PacketChatMessage::handle(PacketHandler *handler) {
    handler->handleChatMessage(this);
}
