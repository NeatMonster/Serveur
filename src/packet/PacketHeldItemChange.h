#ifndef __Serveur__PacketHeldItemChange__
#define __Serveur__PacketHeldItemChange__

#include "ClientPacket.h"

class PacketHeldItemChange : public ClientPacket {
public:
    short_t slot;

    void read(PacketBuffer&);

    void handle(PacketHandler*);
};

#endif /* defined(__Serveur__PacketHeldItemChange__) */
