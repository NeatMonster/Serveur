#ifndef __Serveur__PacketEntityHeadLook__
#define __Serveur__PacketEntityHeadLook__

#include "ServerPacket.h"

class PacketEntityHeadLook : public ServerPacket {
public:
    varint_t entityId;
    byte_t headYaw;

    PacketEntityHeadLook();

    void write(ByteBuffer&);
};

#endif /* defined(__Serveur__PacketEntityHeadLook__) */
