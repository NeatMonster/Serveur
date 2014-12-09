#include "PacketSpawnPlayer.h"

#include "Player.h"

#include <cstring>

PacketSpawnPlayer::PacketSpawnPlayer(Player *player) : ServerPacket(0x0c) {
    entityId = player->getEntityId();
    uuid = player->getUUID();
    x = (int_t) floor_d(player->getX() * 32.);
    y = (int_t) floor_d(player->getY() * 32.);
    z = (int_t) floor_d(player->getZ() * 32.);
    yaw = (byte_t) floor_f(player->getYaw() / 360. * 255.);
    pitch = (byte_t) floor_f(player->getPitch() / 360. * 255.);
    currentItem = 0;
    metadata = ubytes_t(6);
    metadata[0] = 102;
    float_t health = 20;
    std::memcpy(metadata.data() + 1, (ubyte_t*) &health, 4);
    metadata[5] = 127;
}

void PacketSpawnPlayer::write(ByteBuffer &buffer) {
    buffer.putVarInt(entityId);
    UUID uuid(this->uuid);
    buffer.putLong(uuid.msb);
    buffer.putLong(uuid.lsb);
    buffer.putInt(x);
    buffer.putInt(y);
    buffer.putInt(z);
    buffer.putByte(yaw);
    buffer.putByte(pitch);
    buffer.putShort(currentItem);
    buffer.putUBytes(metadata);
}