#ifndef __Serveur__Section__
#define __Serveur__Section__

#include "Types.h"

class Section {
public:
    Section(ubyte_t);

    ~Section();

    ubyte_t getY();

    void initialize(bool);

    ubyte_t getBlockType(int_t);

    ubyte_t getBlockData(int_t);

    ubyte_t getBlockLight(int_t);

    ubyte_t getSkyLight(int_t);

    void setBlockType(int_t, ubyte_t);

    void setBlockData(int_t, ubyte_t);

    void setBlockLight(int_t, ubyte_t);

    void setSkyLight(int_t, ubyte_t);

private:
    ubyte_t y;
    short_t blockCount;
    bool initialized;
    ubyte_t *blockType;
    ubyte_t *blockData;
    ubyte_t *blockLight;
    ubyte_t *skyLight;
};

#endif /* defined(__Serveur__Section__) */
