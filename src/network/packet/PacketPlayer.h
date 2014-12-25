#ifndef __Serveur__PacketPlayer__
#define __Serveur__PacketPlayer__

#include "ClientPacket.h"

class PacketPlayer : public ClientPacket {
public:
    bool onGround;

    void read(PacketBuffer&);

    void handle(PacketHandler*);
};

#endif /* defined(__Serveur__PacketPlayer__) */
