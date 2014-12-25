#include "PacketClientSettings.h"

void PacketClientSettings::read(PacketBuffer &buffer) {
    buffer.getString(locale);
    buffer.getByte(viewDistance);
    buffer.getByte(chatFlags);
    buffer.getBool(chatColours);
    buffer.getUByte(displayedSkinParts);
}
