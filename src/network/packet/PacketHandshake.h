#ifndef __Serveur__PacketHandshake__
#define __Serveur__PacketHandshake__

#include "ClientPacket.h"

class PacketHandshake : public ClientPacket {
public:
    varint_t protocol;
    string_t serverIP;
    ushort_t serverPort;
    varint_t nextState;

    void read(ByteBuffer&);

    void handle(PacketHandler*);
};

#endif /* defined(__Serveur__PacketHandshake__) */
