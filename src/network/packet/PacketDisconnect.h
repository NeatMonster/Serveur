#ifndef __Serveur__PacketDisconnect__
#define __Serveur__PacketDisconnect__

#include "ServerPacket.h"

class PacketDisconnect : public ServerPacket {
public:
    PacketDisconnect(bool, string_t);

    void write(ByteBuffer&);

private:
    string_t reason;
};

#endif /* defined(__Serveur__PacketDisconnect__) */
