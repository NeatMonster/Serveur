#ifndef __Serveur__Types__
#define __Serveur__Types__

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#define BUFFER_SIZE 65535

typedef std::int8_t byte_t;
typedef std::uint8_t ubyte_t;
typedef std::vector<byte_t> bytes_t;
typedef std::vector<ubyte_t> ubytes_t;
typedef std::int16_t short_t;
typedef std::uint16_t ushort_t;
typedef std::int32_t int_t;
typedef std::uint32_t uint_t;
typedef std::uint32_t varint_t;
typedef std::int64_t long_t;
typedef std::uint64_t ulong_t;
typedef float float_t;
typedef double double_t;
typedef std::string string_t;

struct position_t {
    int_t x, y, z;
    long_t pos;

    position_t() {}

    position_t(long_t pos) : x(pos >> 38),
                             y((pos >> 26) & 0xfff),
                             z(pos << 38 >> 38), pos(pos) {}

    position_t(int_t x, int_t y, int_t z) : x(x), y(y), z(z), pos((((long_t) x & 0x3ffffff) << 38)
                                                                | (((long_t) y & 0xfff) << 26)
                                                                | (((long_t) z & 0x3ffffff))) {}
};

struct InvalidArgumentException : std::runtime_error {
    InvalidArgumentException(string_t s) : std::runtime_error(s) {}
};

template<class T>
inline bool contains(T x, std::vector<T> vec) {
    for (T y : vec)
        if (x == y)
            return true;
    return false;
}

inline size_t getSize(uint_t i) {
    if (i < 128)
        return 1;
    else if (i < 16384)
        return 2;
    else if (i < 2097152)
        return 3;
    else if (i < 268435456)
        return 4;
    return 5;
}

#endif /* defined(__Serveur__Types__) */
