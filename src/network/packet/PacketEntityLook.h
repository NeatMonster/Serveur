#ifndef __Serveur__PacketEntityLook__
#define __Serveur__PacketEntityLook__

#include "ServerPacket.h"

class PacketEntityLook : public ServerPacket {
public:
    varint_t entityId;
    byte_t yaw;
    byte_t pitch;
    bool onGround;

    PacketEntityLook();

    void write(ByteBuffer&);
};

#endif /* defined(__Serveur__PacketEntityLook__) */
