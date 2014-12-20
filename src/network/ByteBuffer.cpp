#include "ByteBuffer.h"

#include <arpa/inet.h>
#include <cstring>

ByteBuffer::ByteBuffer() {
    buffer = ubytes_t(BUFFER_SIZE);
    position = limit = 0;
}

void ByteBuffer::get(ubyte_t *b) {
    if (position == limit)
        throw BufferUnderflowException();
    *b = buffer[position++];
}

void ByteBuffer::get(ubyte_t *bs, size_t size) {
    if (position + size > limit)
        throw BufferUnderflowException();
    std::memcpy(bs, &buffer[position], size);
    position += size;
}

void ByteBuffer::getBool(bool &b) {
    get((ubyte_t*) &b);
}

void ByteBuffer::getByte(byte_t &b) {
    get((ubyte_t*) &b);
}

void ByteBuffer::getUByte(ubyte_t &b) {
    get(&b);
}

void ByteBuffer::getBytes(bytes_t &bs) {
    if (bs.size() > 0)
        get((ubyte_t*) bs.data(), bs.size());
}

void ByteBuffer::getUBytes(ubytes_t &bs) {
    if (bs.size() > 0)
        get(bs.data(), bs.size());
}

void ByteBuffer::getShort(short_t &i) {
    get((ubyte_t*) &i, 2);
    i = ntohs(i);
}

void ByteBuffer::getUShort(ushort_t &i) {
    get((ubyte_t*) &i, 2);
    i = ntohs(i);
}

void ByteBuffer::getInt(int_t &i) {
    get((ubyte_t*) &i, 4);
    i = ntohl(i);
}

void ByteBuffer::getUInt(uint_t &i) {
    get((ubyte_t*) &i, 4);
    i = ntohl(i);
}

void ByteBuffer::getVarInt(varint_t &x) {
    x = 0;
    ubyte_t b;
    int shift = 0;
    do {
        get(&b);
        x |= (b & 127) << shift;
        shift += 7;
    } while (b >> 7);
}

void ByteBuffer::getLong(long_t &i) {
    get((ubyte_t*) &i, 8);
    i = (long_t) ntohl(i & 0xffffffff) << 32 | ntohl(i >> 32);
}

void ByteBuffer::getULong(ulong_t &i) {
    get((ubyte_t*) &i, 8);
    i = (long_t) ntohl(i & 0xffffffff) << 32 | ntohl(i >> 32);
}

void ByteBuffer::getFloat(float_t &f) {
    getUInt(*((uint_t*) &f));
}

void ByteBuffer::getDouble(double_t &d) {
    getULong(*((ulong_t*) &d));
}

void ByteBuffer::getString(string_t &s) {
    uint_t size;
    getVarInt(size);
    ubytes_t bs(size);
    getUBytes(bs);
    s = string_t((char*) bs.data(), size);
}

void ByteBuffer::put(ubyte_t *b) {
    if (limit == buffer.size())
        setSize(buffer.size() + 1);
    buffer[position++] = *b;
    if (position > limit)
        limit = position;
}

void ByteBuffer::put(ubyte_t *bs, size_t size) {
    if (limit + size > buffer.size())
        setSize(limit + size);
    std::memcpy(&buffer[position], bs, size);
    position += size;
    if (position > limit)
        limit = position;
}

void ByteBuffer::putBool(bool b) {
    put((ubyte_t*) &b);
}

void ByteBuffer::putByte(byte_t b) {
    put((ubyte_t*) &b);
}

void ByteBuffer::putUByte(ubyte_t b) {
    put(&b);
}

void ByteBuffer::putBytes(bytes_t bs) {
    if (bs.size() > 0)
        put((ubyte_t*) bs.data(), bs.size());
}

void ByteBuffer::putUBytes(ubytes_t bs) {
    if (bs.size() > 0)
        put(bs.data(), bs.size());
}

void ByteBuffer::putShort(short_t i) {
    i = htons(i);
    put((ubyte_t*) &i, 2);
}

void ByteBuffer::putUShort(ushort_t i) {
    i = htons(i);
    put((ubyte_t*) &i, 2);
}

void ByteBuffer::putInt(int_t i) {
    i = htonl(i);
    put((ubyte_t*) &i, 4);
}

void ByteBuffer::putUInt(uint_t i) {
    i = htonl(i);
    put((ubyte_t*) &i, 4);
}

void ByteBuffer::putVarInt(varint_t x) {
    ubyte_t b;
    do {
        b = (x & 127) | ((x > 127) ? 128 : 0);
        put(&b);
        x >>= 7;
    } while (x > 0);
}

void ByteBuffer::putLong(long_t i) {
    i = (long_t) htonl(i & 0xffffffff) << 32 | htonl(i >> 32);
    put((ubyte_t*) &i, 8);
}

void ByteBuffer::putULong(ulong_t i) {
    i = (long_t) htonl(i & 0xffffffff) << 32 | htonl(i >> 32);
    put((ubyte_t*) &i, 8);
};

void ByteBuffer::putFloat(float_t f) {
    putUInt(*((uint_t*) &f));
}

void ByteBuffer::putDouble(double_t d) {
    putULong(*((ulong_t*) &d));
}

void ByteBuffer::putString(string_t s) {
    putVarInt(s.size());
    putUBytes(ubytes_t(s.begin(), s.end()));
}

void ByteBuffer::clear() {
    position = limit = 0;
}

void ByteBuffer::reserve(size_t size) {
    if (size > buffer.size())
        setSize(size);
}

ubyte_t *ByteBuffer::getArray() {
    return buffer.data();
}

size_t ByteBuffer::getLimit() {
    return limit;
}

size_t ByteBuffer::getPosition() {
    return position;
}

size_t ByteBuffer::getSize() {
    return buffer.size();
}

void ByteBuffer::setLimit(size_t limit) {
    if (limit > buffer.size())
        setSize(limit);
    this->limit = limit;
}

void ByteBuffer::setPosition(size_t position) {
    if (position > limit)
        setLimit(position);
    this->position = position;
}

void ByteBuffer::setSize(size_t size) {
    buffer.resize(((size - 1) / BUFFER_SIZE + 1) * BUFFER_SIZE);
}
