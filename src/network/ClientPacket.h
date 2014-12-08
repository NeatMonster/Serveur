#ifndef __Serveur__ClientPacket__
#define __Serveur__ClientPacket__

#include "ByteBuffer.h"
#include "Packet.h"

class PacketHandler;

class ClientPacket : virtual public Packet {
public:
    virtual ~ClientPacket();

    virtual void read(ByteBuffer&) = 0;

    virtual void handle(PacketHandler*);

    void setLength(varint_t);

protected:
    varint_t packetLength;
};

#endif /* defined(__Serveur__ClientPacket__) */
