#ifndef __Serveur__PacketDestroyEntities__
#define __Serveur__PacketDestroyEntities__

#include "ServerPacket.h"

#include <unordered_set>

class PacketDestroyEntities : public ServerPacket {
public:
    PacketDestroyEntities(std::unordered_set<varint_t>);

    void write(ByteBuffer&);

private:
    std::unordered_set<varint_t> entityIds;
};

#endif /* defined(__Serveur__PacketDestroyEntities__) */
