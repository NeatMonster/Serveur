#ifndef __Serveur__PacketPlayerPositionLook__
#define __Serveur__PacketPlayerPositionLook__

#include "ClientPacket.h"
#include "ServerPacket.h"

class PacketPlayerPositionLook : public ClientPacket, public ServerPacket {
public:
    enum Flags {
        NONE = 0x00, X = 0x01, Y = 0x02, Z = 0X04, Y_ROT = 0x08, X_ROT = 0x10
    };

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
