#include "PacketFactory.h"

#include "PacketChatMessage.h"
#include "PacketClientSettings.h"
#include "PacketKeepAlive.h"
#include "PacketPlayer.h"
#include "PacketPlayerAbilities.h"
#include "PacketPlayerLook.h"
#include "PacketPluginMessage.h"
#include "PacketPlayerPosition.h"
#include "PacketPlayerPositionLook.h"

PacketFactory::PacketFactory() {
    registerPacket<PacketKeepAlive>(0x00);
    registerPacket<PacketChatMessage>(0x01);
    registerPacket<PacketPlayer>(0x03);
    registerPacket<PacketPlayerPosition>(0x04);
    registerPacket<PacketPlayerLook>(0x05);
    registerPacket<PacketPlayerPositionLook>(0x06);
    registerPacket<PacketPlayerAbilities>(0x13);
    registerPacket<PacketClientSettings>(0x15);
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
