#ifndef __Serveur__PacketLoginSuccess__
#define __Serveur__PacketLoginSuccess__

#include "ServerPacket.h"

class PacketLoginSuccess : public ServerPacket {
public:
    string_t uuid;
    string_t username;

    PacketLoginSuccess();

    void write(ByteBuffer&);
};

#endif /* defined(__Serveur__PacketLoginSuccess__) */
