#include "PacketEntityMetadata.h"

PacketEntityMetadata::PacketEntityMetadata(varint_t entityId, DataWatcher *metadata) : ServerPacket(0x1c),
    entityId(entityId), metadata(metadata) {}

void PacketEntityMetadata::write(PacketBuffer &buffer) {
    buffer.putVarInt(entityId);
    metadata->write(buffer);
}
