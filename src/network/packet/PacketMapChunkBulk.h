#ifndef __Serveur__PacketMapChunkBulk__
#define __Serveur__PacketMapChunkBulk__

#include "Chunk.h"
#include "ServerPacket.h"

#include <set>
#include <vector>

class PacketMapChunkBulk : public ServerPacket {
public:
    PacketMapChunkBulk(std::set<Chunk*>);

    ~PacketMapChunkBulk();

    void write(ByteBuffer&);

private:
    bool skyLight;
    std::vector<Chunk::Meta> meta;
    int_t size;
    ubyte_t *data;
};

#endif /* defined(__Serveur__PacketMapChunkBulk__) */
