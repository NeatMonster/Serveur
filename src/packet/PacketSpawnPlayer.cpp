#include "PacketSpawnPlayer.h"

#include "EntityPlayer.h"
#include "MathUtils.h"

#include <cstring>

PacketSpawnPlayer::PacketSpawnPlayer(EntityPlayer *player) : ServerPacket(0x0c) {
    entityId = player->getEntityId();
    uuid = player->getUUID();
    x = (int_t) MathUtils::floor_d(player->getX() * 32.);
    y = (int_t) MathUtils::floor_d(player->getY() * 32.);
    z = (int_t) MathUtils::floor_d(player->getZ() * 32.);
    yaw = (byte_t) MathUtils::floor_f(player->getYaw() / 360. * 255.);
    pitch = (byte_t) MathUtils::floor_f(player->getPitch() / 360. * 255.);
    currentItem = 0;
    metadata = ubytes_t(6);
    metadata[0] = 102;
    float_t health = 20;
    std::memcpy(metadata.data() + 1, (ubyte_t*) &health, 4);
    metadata[5] = 127;
}

void PacketSpawnPlayer::write(PacketBuffer &buffer) {
    buffer.putVarInt(entityId);
    buffer.putLong(std::stoull(uuid.substr(0, 8)
                             + uuid.substr(9, 4)
                             + uuid.substr(14, 4), nullptr, 16));
    buffer.putLong(std::stoull(uuid.substr(19, 4)
                             + uuid.substr(24, 12), nullptr, 16));
    buffer.putInt(x);
    buffer.putInt(y);
    buffer.putInt(z);
    buffer.putByte(yaw);
    buffer.putByte(pitch);
    buffer.putShort(currentItem);
    buffer.putUBytes(metadata);
}
