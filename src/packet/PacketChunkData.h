#ifndef __Serveur__PacketChunkData__
#define __Serveur__PacketChunkData__

#include "Chunk.h"
#include "ServerPacket.h"

class PacketChunkData : public ServerPacket {
public:
    PacketChunkData(std::shared_ptr<Chunk>, bool);

    ~PacketChunkData();

    void write(PacketBuffer&);

private:
    Chunk::Meta meta;
    bool continuous;
    int_t size;
    ubyte_t *data;
};

#endif /* defined(__Serveur__PacketChunkData__) */
