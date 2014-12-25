#include "PacketChunkData.h"

PacketChunkData::PacketChunkData(Chunk *chunk, bool unload) : ServerPacket(0x21) {
    continuous = true;
    if (unload) {
        meta = {chunk->getX(), chunk->getZ(), 0};
        size = 0;
        data = nullptr;
    } else {
        meta = chunk->getMeta();
        size_t count = 0;
        for (int i = 0; i < 16; i++)
            if ((meta.bitmask >> i) & 1)
                count++;
        size = 256 + count * 12288;
        data = new ubyte_t[size];
        ubyte_t *data = this->data;
        chunk->write(data);
    }
}

PacketChunkData::~PacketChunkData() {
    delete[] data;
}

void PacketChunkData::write(PacketBuffer &buffer) {
    buffer.putInt(meta.x);
    buffer.putInt(meta.z);
    buffer.putBool(continuous);
    if (size == 0) {
        buffer.putUShort(0);
        buffer.putVarInt(0);
    } else {
        buffer.putUShort(meta.bitmask);
        buffer.putVarInt(size);
        buffer.put(data, size);
    }
}
