#ifndef __Serveur__PacketEntityAction__
#define __Serveur__PacketEntityAction__

#include "ClientPacket.h"

class PacketEntityAction : public ClientPacket {
public:
    varint_t entityId;
    varint_t actionId;
    varint_t jumpBoost;

    void read(ByteBuffer&);
};

#endif /* defined(__Serveur__PacketEntityAction__) */
