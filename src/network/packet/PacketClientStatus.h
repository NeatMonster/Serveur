#ifndef __Serveur__PacketClientStatus__
#define __Serveur__PacketClientStatus__

#include "ClientPacket.h"

class PacketClientStatus : public ClientPacket {
public:
    varint_t actionId;

    PacketClientStatus();

    void read(ByteBuffer&);
};

#endif /* defined(__Serveur__PacketClientStatus__) */
