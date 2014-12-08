#include "PacketAnimation.h"

#include "PacketHandler.h"

PacketAnimation::PacketAnimation() : ServerPacket(0x0b) {}

PacketAnimation::PacketAnimation(varint_t entityId, ubyte_t animationId) : PacketAnimation() {
    this->entityId = entityId;
    this->animationId = animationId;
}

void PacketAnimation::read(ByteBuffer&) {}

void PacketAnimation::write(ByteBuffer &buffer) {
    buffer.putVarInt(entityId);
    buffer.putUByte(animationId);
}

void PacketAnimation::handle(PacketHandler *handler) {
    handler->handleAnimation(this);
}
