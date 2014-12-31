#ifndef __Serveur__PacketPlayerLook__
#define __Serveur__PacketPlayerLook__

#include "ClientPacket.h"

class PacketPlayerLook : public ClientPacket {
public:
    float_t yaw;
    float_t pitch;
    bool onGround;

    void read(PacketBuffer&);

    void handle(PacketHandler*);
};

#endif /* defined(__Serveur__PacketPlayerLook__) */
