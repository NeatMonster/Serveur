#ifndef __Serveur__PacketEntityMove__
#define __Serveur__PacketEntityMove__

#include "ServerPacket.h"

class PacketEntityMove : public ServerPacket {
public:
    varint_t entityId;
    byte_t dX;
    byte_t dY;
    byte_t dZ;
    bool onGround;

    PacketEntityMove();

    void write(ByteBuffer&);
};

#endif /* defined(__Serveur__PacketEntityMove__) */
