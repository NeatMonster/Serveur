#ifndef __Serveur__PacketPlayerPosition__
#define __Serveur__PacketPlayerPosition__

#include "ClientPacket.h"

class PacketPlayerPosition : public ClientPacket {
public:
    double_t x;
    double_t y;
    double_t z;
    bool onGround;

    void read(ByteBuffer&);

    void handle(PacketHandler*);
};

#endif /* defined(__Serveur__PacketPlayerPosition__) */
