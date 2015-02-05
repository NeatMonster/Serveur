#include "Section.h"

#include <cstring>

Section::Section(ubyte_t y) : y(y), blockCount(0), initialized(false),
    blockData(nullptr), blockLight(nullptr), skyLight(nullptr) {}

Section::~Section() {
    if (initialized) {
        delete[] blockData;
        delete[] blockLight;
        delete[] skyLight;
    }
}

ubyte_t Section::getY() {
    return y;
}

void Section::initialize(bool fill) {
    if (!initialized) {
        blockData = new ushort_t[4096];
        blockLight = new ubyte_t[2048];
        skyLight = new ubyte_t[2048];
        if (fill) {
            std::memset(blockData, 0, 8192);
            std::memset(blockLight, 0, 2048);
            std::memset(skyLight, 255, 2048);
        }
        initialized = true;
    }
}

ubyte_t Section::getBlockType(int_t index) {
    return initialized ? ((blockData[index] & 0xff0) >> 4) & 0xff : 0;
}

ubyte_t Section::getBlockData(int_t index) {
    return initialized ? blockData[index] & 0xf : 0;
}

ubyte_t Section::getBlockLight(int_t index) {
    if (initialized) {
        if (index % 2 == 0)
            return blockLight[index / 2] & 0x0f;
        else
            return (blockLight[index / 2] & 0xf0) >> 4;
    } else
        return 0;
}

ubyte_t Section::getSkyLight(int_t index) {
    if (initialized) {
        if (index % 2 == 0)
            return skyLight[index / 2] & 0x0f;
        else
            return (skyLight[index / 2] & 0xf0) >> 4;
    } else
        return 15;
}

void Section::setBlockType(int_t index, ubyte_t type) {
    ubyte_t oldType = getBlockType(index);
    if (type > 0 && oldType == 0)
        ++blockCount;
    else if (type == 0 && oldType > 0)
        blockCount--;
    blockData[index] = ((type & 0xff) << 4) | (blockData[index] & 0xf);
}

void Section::setBlockData(int_t index, ubyte_t data) {
    blockData[index] = (blockData[index] & 0xff0) | (data & 0xf);
}

void Section::setBlockLight(int_t index, ubyte_t light) {
    if (index % 2 == 0)
        blockLight[index / 2] &= 0xf0 | (light & 0x0f);
    else
        blockLight[index / 2] &= 0x0f | ((light & 0x0f) << 4);
}

void Section::setSkyLight(int_t index, ubyte_t light) {
    if (index % 2 == 0)
        skyLight[index / 2] &= 0xf0 | (light & 0x0f);
    else
        skyLight[index / 2] &= 0x0f | ((light & 0x0f) << 4);
}
