#ifndef __Serveur__PacketPlayerDigging__
#define __Serveur__PacketPlayerDigging__

#include "ClientPacket.h"

class PacketPlayerDigging : public ClientPacket {
public:
    varint_t status;
    position_t location;
    ubyte_t face;

    void read(ByteBuffer&);
};

#endif /* defined(__Serveur__PacketPlayerDigging__) */
