#ifndef __Serveur__PacketTimeUpdate__
#define __Serveur__PacketTimeUpdate__

#include "ServerPacket.h"

class PacketTimeUpdate : public ServerPacket {
public:
    long_t time;
    long_t dayTime;

    PacketTimeUpdate(long_t, long_t);

    void write(ByteBuffer&);
};

#endif /* defined(__Serveur__PacketTimeUpdate__) */
