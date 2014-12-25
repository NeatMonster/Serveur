#ifndef __Serveur__PacketLoginStart__
#define __Serveur__PacketLoginStart__

#include "ClientPacket.h"

class PacketLoginStart : public ClientPacket {
public:
    string_t name;

    void read(PacketBuffer&);

    void handle(PacketHandler*);
};

#endif /* defined(__Serveur__PacketLoginStart__) */
