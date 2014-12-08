#ifndef __Serveur__PacketAnimation__
#define __Serveur__PacketAnimation__

#include "ClientPacket.h"
#include "ServerPacket.h"

class PacketAnimation : public ClientPacket, public ServerPacket {
public:
    varint_t entityId;
    ubyte_t animationId;

    PacketAnimation();

    PacketAnimation(varint_t, ubyte_t);

    void read(ByteBuffer&);

    void write(ByteBuffer&);

    void handle(PacketHandler*);
};


#endif /* defined(__Serveur__PacketAnimation__) */
