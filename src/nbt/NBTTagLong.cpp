#include "NBTTagLong.h"

NBTTagLong::NBTTagLong() : NBTTag(Type::LONG) {}

void NBTTagLong::read(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    *(((ubyte_t*) &value) + 7) = *(data++);
    *(((ubyte_t*) &value) + 6) = *(data++);
    *(((ubyte_t*) &value) + 5) = *(data++);
    *(((ubyte_t*) &value) + 4) = *(data++);
    *(((ubyte_t*) &value) + 3) = *(data++);
    *(((ubyte_t*) &value) + 2) = *(data++);
    *(((ubyte_t*) &value) + 1) = *(data++);
    *(((ubyte_t*) &value) + 0) = *(data++);
}

void NBTTagLong::write(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    *(data++) = *(((ubyte_t*) &value) + 7);
    *(data++) = *(((ubyte_t*) &value) + 6);
    *(data++) = *(((ubyte_t*) &value) + 5);
    *(data++) = *(((ubyte_t*) &value) + 4);
    *(data++) = *(((ubyte_t*) &value) + 3);
    *(data++) = *(((ubyte_t*) &value) + 2);
    *(data++) = *(((ubyte_t*) &value) + 1);
    *(data++) = *(((ubyte_t*) &value) + 0);
}

void NBTTagLong::print(int tab, bool header) {
    NBTTag::print(tab, header);
    std::cout << "TAG_Long(" << (header ? ("'" + name + "'") : "None") << "): " << value << std::endl;
}

long_t NBTTagLong::get() {
    return value;
}

void NBTTagLong::set(long_t value) {
    this->value = value;
}