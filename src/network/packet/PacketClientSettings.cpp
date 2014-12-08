#include "PacketClientSettings.h"

void PacketClientSettings::read(ByteBuffer &buffer) {
    buffer.getString(locale);
    buffer.getByte(viewDistance);
    buffer.getByte(chatFlags);
    buffer.getBool(chatColours);
    buffer.getUByte(displayedSkinParts);
}
