#ifndef __Serveur__PacketCollectItem__
#define __Serveur__PacketCollectItem__

#include "ServerPacket.h"

class PacketCollectItem : public ServerPacket {
public:
    varint_t collectedId;
    varint_t collectorId;

    PacketCollectItem();

    void write(PacketBuffer&);
};

#endif /* defined(__Serveur__PacketCollectItem__) */
