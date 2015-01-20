#include "Compression.h"

#include <cstring>

#include "zlib/zlib.h"


Compression::result_t Compression::inflateGzip(ubyte_t *in, size_t inSize) {
    z_stream stream;
    std::memset(&stream, 0, sizeof(stream));
    stream.next_in = in;
    stream.avail_in = inSize;
    ubyte_t *buffer = new ubyte_t[BUFFER_SIZE];
    stream.next_out = buffer;
    stream.avail_out = BUFFER_SIZE;
    inflateInit2(&stream, MAX_WBITS | 16);
    std::vector<ubyte_t*> buffers;
    while (true) {
        int ret = inflate(&stream, Z_NO_FLUSH);
        buffers.push_back(buffer);
        if (ret == Z_OK) {
            buffer = new ubyte_t[BUFFER_SIZE];
            stream.next_out = buffer;
            stream.avail_out = BUFFER_SIZE;
        } else if (ret == Z_STREAM_END)
            break;
        else
            throw new CompressionException("Inflate returned " + std::to_string(ret));
    }
    size_t outSize = stream.total_out;
    inflateEnd(&stream);
    ubyte_t *out = (ubyte_t*) std::malloc(outSize);
    for (size_t i = 0; i < buffers.size(); i++) {
        std::memcpy(out + i * BUFFER_SIZE, buffers[i], min<size_t>(BUFFER_SIZE, outSize - i * BUFFER_SIZE));
        delete[] buffers[i];
    }
    return {out, outSize};
}

Compression::result_t Compression::inflateZlib(ubyte_t *in, size_t inSize) {
    z_stream stream;
    stream.zalloc = (alloc_func) nullptr;
    stream.zfree = (free_func) nullptr;
    stream.opaque = nullptr;
    inflateInit(&stream);
    stream.next_in = in;
    stream.avail_in = inSize;
    ubyte_t *buffer = new ubyte_t[BUFFER_SIZE];
    std::vector<ubyte_t*> buffers;
    stream.next_out = buffer;
    stream.avail_out = BUFFER_SIZE;
    while (true) {
        int ret = inflate(&stream, Z_NO_FLUSH);
        buffers.push_back(buffer);
        if (ret == Z_OK) {
            buffer = new ubyte_t[BUFFER_SIZE];
            stream.next_out = buffer;
            stream.avail_out = BUFFER_SIZE;
        } else if (ret == Z_STREAM_END)
            break;
        else
            throw new CompressionException("Inflate returned " + std::to_string(ret));
    }
    size_t outSize = stream.total_out;
    inflateEnd(&stream);
    ubyte_t *out = (ubyte_t*) std::malloc(outSize);
    for (size_t i = 0; i < buffers.size(); i++) {
        std::memcpy(out + i * BUFFER_SIZE, buffers[i], min<size_t>(BUFFER_SIZE, outSize - i * BUFFER_SIZE));
        delete[] buffers[i];
    }
    return {out, outSize};
}
