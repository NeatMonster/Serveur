#ifndef __Serveur__PacketTimeUpdate__
#define __Serveur__PacketTimeUpdate__

#include "ServerPacket.h"

class PacketTimeUpdate : public ServerPacket {
public:
    long_t worldAge;
    long_t dayTime;

    PacketTimeUpdate();

    void write(ByteBuffer&);
};

#endif /* defined(__Serveur__PacketTimeUpdate__) */
