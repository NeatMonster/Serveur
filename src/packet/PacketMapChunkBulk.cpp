#include "PacketMapChunkBulk.h"

PacketMapChunkBulk::PacketMapChunkBulk(std::vector<Chunk*> chunks) : ServerPacket(0x26) {
    skyLight = true;
    size = 0;
    for (Chunk *chunk : chunks) {
        Chunk::Meta meta = chunk->getMeta();
        this->meta.push_back(meta);
        size_t count = 0;
        for (int i = 0; i < 16; ++i)
            if ((meta.bitmask >> i) & 1)
                ++count;
        size += 256 + count * 12288;
    }
    data = new ubyte_t[size];
    ubyte_t *data = this->data;
    for (Chunk *chunk : chunks)
        chunk->write(data);
}

PacketMapChunkBulk::~PacketMapChunkBulk() {
    delete[] data;
}

void PacketMapChunkBulk::write(PacketBuffer &buffer) {
    buffer.putBool(skyLight);
    buffer.putVarInt(meta.size());
    for (Chunk::Meta &meta : this->meta) {
        buffer.putInt(meta.x);
        buffer.putInt(meta.z);
        buffer.putUShort(meta.bitmask);
    }
    buffer.put(data, size);
}
