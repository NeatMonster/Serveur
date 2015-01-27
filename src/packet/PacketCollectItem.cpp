#include "PacketCollectItem.h"

PacketCollectItem::PacketCollectItem() : ServerPacket(0x0d) {}

void PacketCollectItem::write(PacketBuffer &buffer) {
    buffer.putVarInt(collectedId);
    buffer.putVarInt(collectorId);
}
