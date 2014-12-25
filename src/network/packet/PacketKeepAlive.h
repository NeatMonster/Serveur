#ifndef __Serveur__PacketKeepAlive__
#define __Serveur__PacketKeepAlive__

#include "ClientPacket.h"
#include "ServerPacket.h"

class PacketKeepAlive : public ClientPacket, public ServerPacket {
public:
    varint_t keepAliveId;

    PacketKeepAlive();

    PacketKeepAlive(varint_t);

    void read(PacketBuffer&);

    void write(PacketBuffer&);

    void handle(PacketHandler*);
};

#endif /* defined(__Serveur__PacketKeepAlive__) */
