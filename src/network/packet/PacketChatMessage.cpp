#include "PacketChatMessage.h"

PacketChatMessage::PacketChatMessage() : ClientPacket(0x02), ServerPacket(0x02) {};

PacketChatMessage::PacketChatMessage(string_t message) : PacketChatMessage() {
    this->message = message;
    position = 0;
};

void PacketChatMessage::read(ByteBuffer &buffer) {
    buffer.getString(message);
}

void PacketChatMessage::write(ByteBuffer &buffer) {
    buffer.putString(message);
    buffer.putByte(position);
}

void PacketChatMessage::handle(PacketHandler *handler) {
    handler->handleChatMessage(this);
}
