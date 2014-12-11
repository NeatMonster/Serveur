#ifndef __Serveur__Compression__
#define __Serveur__Compression__

#include "Types.h"

class Compression {
public:
    class CompressionException: public std::runtime_error {
    public:
        CompressionException(string_t s) : std::runtime_error(s) {}
    };

    typedef std::pair<ubyte_t*, size_t> result_t;

    static result_t inflateGzip(ubyte_t*, size_t);
};

#endif /* defined(__Serveur__Compression__) */
