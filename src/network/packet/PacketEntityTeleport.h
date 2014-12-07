#ifndef __Serveur__PacketEntityTeleport__
#define __Serveur__PacketEntityTeleport__

#include "ServerPacket.h"

class PacketEntityTeleport : public ServerPacket {
public:
    varint_t entityId;
    int_t x;
    int_t y;
    int_t z;
    byte_t yaw;
    byte_t pitch;
    bool onGround;

    PacketEntityTeleport();

    void write(ByteBuffer&);
};

#endif /* defined(__Serveur__PacketEntityTeleport__) */
