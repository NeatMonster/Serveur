#ifndef __Serveur__ClientPacket__
#define __Serveur__ClientPacket__

#include "ByteBuffer.h"
#include "Packet.h"
#include "PacketHandler.h"

class ClientPacket : public Packet {
public:
    ClientPacket(varint_t);

    virtual ~ClientPacket();

    virtual void read(ByteBuffer&) = 0;

    virtual void handle(PacketHandler*) = 0;
};

#endif /* defined(__Serveur__ClientPacket__) */
