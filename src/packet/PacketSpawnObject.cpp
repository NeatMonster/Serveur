#include "PacketSpawnObject.h"

#include "Entity.h"

PacketSpawnObject::PacketSpawnObject(Entity *entity) : ServerPacket(0x0e) {
    entityId = entity->getEntityId();
    type = entity->getType();
    x = (int_t) floor_d(entity->getX() * 32.);
    y = (int_t) floor_d(entity->getY() * 32.);
    z = (int_t) floor_d(entity->getZ() * 32.);
    yaw = (byte_t) floor_f(entity->getYaw() / 360. * 256.);
    pitch = (byte_t) floor_f(entity->getPitch() / 360. * 256.);
    data = 0;
}

void PacketSpawnObject::write(PacketBuffer &buffer) {
    buffer.putVarInt(entityId);
    buffer.putByte(type);
    buffer.putInt(x);
    buffer.putInt(y);
    buffer.putInt(z);
    buffer.putByte(pitch);
    buffer.putByte(yaw);
    buffer.putInt(data);
}
