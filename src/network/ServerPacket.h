#ifndef __Serveur__ServerPacket__
#define __Serveur__ServerPacket__

#include "Packet.h"
#include "PacketBuffer.h"

class ServerPacket : virtual public Packet {
public:
    ServerPacket(varint_t packetId);

    virtual ~ServerPacket();

    virtual void write(PacketBuffer&) = 0;

    varint_t getPacketId();

private:
    varint_t packetId;
};

#endif /* defined(__Serveur__ServerPacket__) */
