#ifndef __Serveur__PacketEntityVelocity__
#define __Serveur__PacketEntityVelocity__

#include "ServerPacket.h"

class PacketEntityVelocity : public ServerPacket {
public:
    varint_t entityId;
    short_t velocityX;
    short_t velocityY;
    short_t velocityZ;

    PacketEntityVelocity();
        
    void write(PacketBuffer&);
};

#endif /* defined(__Serveur__PacketEntityVelocity__) */
