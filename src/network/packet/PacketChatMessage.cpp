#include "PacketChatMessage.h"

PacketChatMessage::PacketChatMessage(string_t message) : ClientPacket(0x02), ServerPacket(0x02) {
    this->message = message;
    position = 0;
};

void PacketChatMessage::write(ByteBuffer &buffer) {
    buffer.putString(message);
    buffer.putByte(position);
}

void PacketChatMessage::read(ByteBuffer &buffer) {
    buffer.getString(message);
}

void PacketChatMessage::handle(PacketHandler *handler) {
    handler->handleChatMessage(this);
}
