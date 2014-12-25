#include "PacketDestroyEntities.h"

PacketDestroyEntities::PacketDestroyEntities(std::unordered_set<varint_t> entityIds) : ServerPacket(0x13) {
    this->entityIds = entityIds;
}

void PacketDestroyEntities::write(PacketBuffer &buffer) {
    buffer.putVarInt(entityIds.size());
    for (varint_t const &entityId : entityIds)
        buffer.putVarInt(entityId);
}
