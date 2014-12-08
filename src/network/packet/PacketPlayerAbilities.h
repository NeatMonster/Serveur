#ifndef __Serveur__PacketPlayerAbilities__
#define __Serveur__PacketPlayerAbilities__

#include "ClientPacket.h"
#include "ServerPacket.h"

class PacketPlayerAbilities : public ClientPacket, public ServerPacket {
public:
    bool godMode;
    bool canFly;
    bool isFlying;
    bool creativeMode;
    float_t flyingSpeed;
    float_t walkingSpeed;

    PacketPlayerAbilities();

    void write(ByteBuffer&);

    void read(ByteBuffer&);
};

#endif /* defined(__Serveur__PacketPlayerAbilities__) */
