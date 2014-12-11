#include "NBTTagShort.h"

NBTTagShort::NBTTagShort() : NBTTag(Type::SHORT) {}

void NBTTagShort::read(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    *(((ubyte_t*) &value) + 1) = *(data++);
    *(((ubyte_t*) &value) + 0) = *(data++);
}

void NBTTagShort::write(ubyte_t *&data, bool header) {
    NBTTag::write(data, header);
    *(data++) = *(((ubyte_t*) &value) + 1);
    *(data++) = *(((ubyte_t*) &value) + 0);
}

void NBTTagShort::print(int tab, bool header) {
    NBTTag::print(tab, header);
    std::cout << "TAG_Short(" << (header ? ("'" + name + "'") : "None") << "): " << value << std::endl;
}

short_t NBTTagShort::get() {
    return value;
}

void NBTTagShort::set(short_t value) {
    this->value = value;
}
