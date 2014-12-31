#ifndef __Serveur__PacketTimeUpdate__
#define __Serveur__PacketTimeUpdate__

#include "ServerPacket.h"

class PacketTimeUpdate : public ServerPacket {
public:
    PacketTimeUpdate(long_t, long_t);

    void write(PacketBuffer&);

private:
    long_t time;
    long_t dayTime;
};

#endif /* defined(__Serveur__PacketTimeUpdate__) */
