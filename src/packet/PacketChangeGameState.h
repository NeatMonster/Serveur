#ifndef __Serveur__PacketChangeGameState__
#define __Serveur__PacketChangeGameState__

#include "ServerPacket.h"

class PacketChangeGameState : public ServerPacket {
public:
    ubyte_t reason;
    float_t value;

    PacketChangeGameState();

    void write(PacketBuffer&);
};

#endif /* defined(__Serveur__PacketChangeGameState__) */
