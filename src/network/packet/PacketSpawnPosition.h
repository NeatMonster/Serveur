#ifndef __Serveur__PacketSpawnPosition__
#define __Serveur__PacketSpawnPosition__

#include "ServerPacket.h"

class PacketSpawnPosition : public ServerPacket {
public:
    PacketSpawnPosition(int_t, int_t, int_t);

    void write(ByteBuffer&);

private:
    position_t location;
};

#endif /* defined(__Serveur__PacketSpawnPosition__) */
