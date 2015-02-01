#include "PacketUpdateHealth.h"

PacketUpdateHealth::PacketUpdateHealth() : ServerPacket(0x06) {}

void PacketUpdateHealth::write(PacketBuffer& buffer) {
    buffer.putFloat(health);
    buffer.putVarInt(foodLevel);
    buffer.putFloat(foodSaturationLevel);
}
