#ifndef __Serveur__PacketDestroyEntities__
#define __Serveur__PacketDestroyEntities__

#include "ServerPacket.h"

#include <set>

class PacketDestroyEntities : public ServerPacket {
public:
    PacketDestroyEntities(std::set<varint_t>);

    void write(ByteBuffer&);

private:
    std::set<varint_t> entityIds;
};

#endif /* defined(__Serveur__PacketDestroyEntities__) */
