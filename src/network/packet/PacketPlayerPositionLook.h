#ifndef __Serveur__PacketPlayerPositionLook__
#define __Serveur__PacketPlayerPositionLook__

#include "ClientPacket.h"
#include "ServerPacket.h"

class PacketPlayerPositionLook : public ClientPacket, public ServerPacket {
public:
    double_t x;
    double_t y;
    double_t z;
    float_t yaw;
    float_t pitch;
    bool onGround;
    byte_t flags;

    PacketPlayerPositionLook();

    void read(ByteBuffer&);

    void write(ByteBuffer&);

    void handle(PacketHandler*);
};

#endif /* defined(__Serveur__PacketPlayerPositionLook__) */
