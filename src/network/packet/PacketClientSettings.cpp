#include "PacketClientSettings.h"

PacketClientSettings::PacketClientSettings() : ClientPacket(0x15) {}

void PacketClientSettings::read(ByteBuffer &buffer) {
    buffer.getString(locale);
    buffer.getByte(viewDistance);
    buffer.getByte(chatFlags);
    buffer.getBool(chatColours);
    buffer.getUByte(displayedSkinParts);
}
