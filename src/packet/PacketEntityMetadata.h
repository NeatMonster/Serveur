#ifndef __Serveur__PacketEntityMetadata__
#define __Serveur__PacketEntityMetadata__

#include "DataWatcher.h"
#include "ServerPacket.h"

class PacketEntityMetadata : public ServerPacket {
public:
    PacketEntityMetadata(varint_t, DataWatcher*);

    void write(PacketBuffer&);

private:
    varint_t entityId;
    DataWatcher *metadata;
};

#endif /* defined(__Serveur__PacketEntityMetadata__) */
