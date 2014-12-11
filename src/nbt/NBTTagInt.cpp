#include "NBTTagInt.h"

NBTTagInt::NBTTagInt() : NBTTag(Type::INT) {}

void NBTTagInt::read(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    *(((ubyte_t*) &value) + 3) = *(data++);
    *(((ubyte_t*) &value) + 2) = *(data++);
    *(((ubyte_t*) &value) + 1) = *(data++);
    *(((ubyte_t*) &value) + 0) = *(data++);
}

void NBTTagInt::write(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    *(data++) = *(((ubyte_t*) &value) + 3);
    *(data++) = *(((ubyte_t*) &value) + 2);
    *(data++) = *(((ubyte_t*) &value) + 1);
    *(data++) = *(((ubyte_t*) &value) + 0);
}

void NBTTagInt::print(int tab, bool header) {
    NBTTag::print(tab, header);
    std::cout << "TAG_Int(" << (header ? ("'" + name + "'") : "None") << "): " << value << std::endl;
}

int_t NBTTagInt::get() {
    return value;
}

void NBTTagInt::set(int_t value) {
    this->value = value;
}
