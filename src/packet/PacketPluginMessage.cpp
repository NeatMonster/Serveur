#include "PacketPluginMessage.h"

void PacketPluginMessage::read(PacketBuffer &buffer) {
    size_t start = buffer.getPosition();
    buffer.getString(channel);
    data = ubytes_t(packetLength - 1 + start - buffer.getPosition());
    buffer.getUBytes(data);
}
