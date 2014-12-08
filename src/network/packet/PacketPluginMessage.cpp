#include "PacketPluginMessage.h"

PacketPluginMessage::PacketPluginMessage() : ClientPacket(0x17) {}

void PacketPluginMessage::read(ByteBuffer &buffer) {
    size_t start = buffer.getPosition();
    buffer.getString(channel);
    data = ubytes_t(packetLength - 1 + start - buffer.getPosition());
    buffer.getUBytes(data);
}
