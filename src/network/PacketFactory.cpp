#include "PacketFactory.h"

#include "PacketAnimation.h"
#include "PacketChatMessage.h"
#include "PacketClientSettings.h"
#include "PacketClientStatus.h"
#include "PacketEntityAction.h"
#include "PacketHeldItemChange.h"
#include "PacketKeepAlive.h"
#include "PacketPlayer.h"
#include "PacketPlayerAbilities.h"
#include "PacketPlayerDigging.h"
#include "PacketPlayerLook.h"
#include "PacketPluginMessage.h"
#include "PacketPlayerPosition.h"
#include "PacketPlayerPositionLook.h"
#include "PacketUseEntity.h"

PacketFactory::PacketFactory() {
    registerPacket<PacketKeepAlive>(0x00);
    registerPacket<PacketChatMessage>(0x01);
    registerPacket<PacketUseEntity>(0x02);
    registerPacket<PacketPlayer>(0x03);
    registerPacket<PacketPlayerPosition>(0x04);
    registerPacket<PacketPlayerLook>(0x05);
    registerPacket<PacketPlayerPositionLook>(0x06);
    registerPacket<PacketPlayerDigging>(0x07);
    registerPacket<PacketHeldItemChange>(0x09);
    registerPacket<PacketAnimation>(0x0a);
    registerPacket<PacketEntityAction>(0x0b);
    registerPacket<PacketPlayerAbilities>(0x13);
    registerPacket<PacketClientSettings>(0x15);
    registerPacket<PacketClientStatus>(0x16);
    registerPacket<PacketPluginMessage>(0x17);
}

ClientPacket *PacketFactory::createPacket(const varint_t packetId) {
    return packets.find(packetId)->second();
}

bool PacketFactory::hasPacket(const varint_t packetId) {
    return packets.find(packetId) != packets.end();
}

template<typename T>
ClientPacket *PacketFactory::constructPacket() {
    return new T;
}

template<typename T>
void PacketFactory::registerPacket(const varint_t packetId) {
    packets.insert(std::make_pair(packetId, &PacketFactory::constructPacket<T>));
}
