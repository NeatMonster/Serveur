#include "PacketEntityMetadata.h"

#include "Metadata.h"

PacketEntityMetadata::PacketEntityMetadata(varint_t entityId, Metadata *metadata) : ServerPacket(0x1c),
    entityId(entityId), metadata(metadata) {}

PacketEntityMetadata::~PacketEntityMetadata() {
    delete metadata;
}

void PacketEntityMetadata::write(PacketBuffer &buffer) {
    buffer.putVarInt(entityId);
    metadata->write(buffer);
}
