#include "PacketChatMessage.h"

PacketChatMessage::PacketChatMessage() : ServerPacket(0x02) {};

PacketChatMessage::PacketChatMessage(string_t message) : PacketChatMessage() {
    this->message = message;
    position = 0;
};

void PacketChatMessage::read(PacketBuffer &buffer) {
    buffer.getString(message);
}

void PacketChatMessage::write(PacketBuffer &buffer) {
    buffer.putString(message);
    buffer.putByte(position);
}

void PacketChatMessage::handle(PacketHandler *handler) {
    handler->handleChatMessage(this);
}
