#ifndef __Serveur__PacketEntityMetadata__
#define __Serveur__PacketEntityMetadata__

#include "ServerPacket.h"

class Metadata;

class PacketEntityMetadata : public ServerPacket {
public:
    PacketEntityMetadata(varint_t, Metadata*);

    ~PacketEntityMetadata();

    void write(PacketBuffer&);

private:
    varint_t entityId;
    Metadata *metadata;
};

#endif /* defined(__Serveur__PacketEntityMetadata__) */
