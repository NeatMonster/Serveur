#ifndef __Serveur__PacketLoginSuccess__
#define __Serveur__PacketLoginSuccess__

#include "ServerPacket.h"

class PacketLoginSuccess : public ServerPacket {
public:
    PacketLoginSuccess(string_t, string_t);

    void write(ByteBuffer&);

private:
    string_t uuid;
    string_t name;
};

#endif /* defined(__Serveur__PacketLoginSuccess__) */
