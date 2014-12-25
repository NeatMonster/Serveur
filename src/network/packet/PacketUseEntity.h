#ifndef __Serveur__PacketUseEntity__
#define __Serveur__PacketUseEntity__

#include "ClientPacket.h"

class PacketUseEntity : public ClientPacket {
public:
    varint_t target;
    varint_t type;
    float_t targetX;
    float_t targetY;
    float_t targetZ;

    void read(PacketBuffer&);
};

#endif /* defined(__Serveur__PacketUseEntity__) */
