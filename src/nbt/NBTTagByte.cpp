#include "NBTTagByte.h"

NBTTagByte::NBTTagByte() : NBTTag(Type::BYTE) {}

void NBTTagByte::read(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    value = *(data++);
}

void NBTTagByte::write(ubyte_t *&data, bool header) {
    NBTTag::write(data, header);
    *(data++) = value;
}

void NBTTagByte::print(int tab, bool header) {
    NBTTag::print(tab, header);
    std::cout << "TAG_Byte(" << (header ? ("'" + name + "'") : "None") << "): " << (int) value << std::endl;
}

byte_t NBTTagByte::get() {
    return value;
}

void NBTTagByte::set(byte_t value) {
    this->value = value;
}
