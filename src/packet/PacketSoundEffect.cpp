#include "PacketSoundEffect.h"

PacketSoundEffect::PacketSoundEffect() : ServerPacket(0x29) {}

void PacketSoundEffect::write(PacketBuffer &buffer) {
    buffer.putString(soundName);
    buffer.putInt(positionX);
    buffer.putInt(positionY);
    buffer.putInt(positionZ);
    buffer.putFloat(volume);
    buffer.putUByte(pitch);
}
