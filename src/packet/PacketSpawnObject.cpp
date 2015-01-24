#include "PacketSpawnObject.h"

#include "Entity.h"
#include "MathUtils.h"

PacketSpawnObject::PacketSpawnObject(Entity *entity, int_t data) : ServerPacket(0x0e) {
    entityId = entity->getEntityId();
    type = entity->getType();
    x = (int_t) MathUtils::floor_d(entity->getX() * 32.);
    y = (int_t) MathUtils::floor_d(entity->getY() * 32.);
    z = (int_t) MathUtils::floor_d(entity->getZ() * 32.);
    yaw = (byte_t) MathUtils::floor_f(entity->getYaw() / 360. * 256.);
    pitch = (byte_t) MathUtils::floor_f(entity->getPitch() / 360. * 256.);
    this->data = data;
    if (data > 0) {
        motX = (short_t) MathUtils::floor_d(entity->getVelocityX() * 8000.);
        motY = (short_t) MathUtils::floor_d(entity->getVelocityY() * 8000.);
        motZ = (short_t) MathUtils::floor_d(entity->getVelocityZ() * 8000.);
    }
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
    if (data > 0) {
        buffer.putShort(motX);
        buffer.putShort(motY);
        buffer.putShort(motZ);
    }
}
