#ifndef __Serveur__PacketDisconnect__
#define __Serveur__PacketDisconnect__

#include "ServerPacket.h"

class PacketDisconnect : public ServerPacket {
public:
    string_t reason;

    PacketDisconnect();

    void write(ByteBuffer&);
};

#endif /* defined(__Serveur__PacketDisconnect__) */
