#ifndef __Serveur__PacketChunkData__
#define __Serveur__PacketChunkData__

#include "Chunk.h"
#include "ServerPacket.h"

class PacketChunkData : public ServerPacket {
public:
    Chunk::Meta meta;
    bool continuous;
    int_t size;
    ubyte_t *data;

    PacketChunkData(Chunk*, bool);

    ~PacketChunkData();

    void write(ByteBuffer&);
};

#endif /* defined(__Serveur__PacketChunkData__) */
