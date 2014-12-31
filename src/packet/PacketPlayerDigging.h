#ifndef __Serveur__PacketPlayerDigging__
#define __Serveur__PacketPlayerDigging__

#include "ClientPacket.h"

class PacketPlayerDigging : public ClientPacket {
public:
    varint_t status;
    Position location;
    ubyte_t face;

    void read(PacketBuffer&);
};

#endif /* defined(__Serveur__PacketPlayerDigging__) */
