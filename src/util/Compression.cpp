#include "Compression.h"

#include "zlib/zlib.h"

#include <cstring>

Compression::result_t Compression::inflateGzip(ubyte_t *in, size_t inSize) {
    size_t outSize = 0;
    std::vector<size_t> bufferSizes;
    std::vector<ubyte_t*> bufferPtrs;
    ubyte_t *buffer = new ubyte_t[BUFFER_SIZE];
    z_stream stream;
    memset(&stream, 0, sizeof(stream));
    stream.next_in = in;
    stream.avail_in = inSize;
    stream.next_out = buffer;
    stream.avail_out = BUFFER_SIZE;
    inflateInit2(&stream, MAX_WBITS | 16);
    while (true) {
        int ret = inflate(&stream, Z_NO_FLUSH);
        outSize += stream.total_out;
        bufferPtrs.push_back(buffer);
        bufferSizes.push_back(stream.total_out);
        if (ret == Z_OK) {
            buffer = new ubyte_t[BUFFER_SIZE];
            stream.next_out = buffer;
            stream.avail_out = BUFFER_SIZE;
        } else if (ret == Z_STREAM_END)
            break;
        else
            throw new CompressionException("Inflate returned " + std::to_string(ret));
    }
    inflateEnd(&stream);
    size_t currentSize = 0;
    ubyte_t *out = (ubyte_t*) malloc(outSize);
    for (size_t i = 0; i < bufferPtrs.size(); i++) {
        memcpy(out + currentSize, bufferPtrs[i], bufferSizes[i]);
        currentSize += bufferSizes[i];
        delete bufferPtrs[i];
    }
    return {out, outSize};
}
