#ifndef __Serveur__PacketEntityMoveLook__
#define __Serveur__PacketEntityMoveLook__

#include "ServerPacket.h"

class PacketEntityMoveLook : public ServerPacket {
public:
    varint_t entityId;
    byte_t dX;
    byte_t dY;
    byte_t dZ;
    byte_t yaw;
    byte_t pitch;
    bool onGround;

    PacketEntityMoveLook();

    void write(PacketBuffer&);
};

#endif /* defined(__Serveur__PacketEntityMoveLook__) */
