#include "NBTTagFloat.h"

NBTTagFloat::NBTTagFloat() : NBTTag(Type::FLOAT) {}

NBTTagFloat::NBTTagFloat(NBTTagFloat *tag) : NBTTag(tag), value(tag->value) {}

void NBTTagFloat::read(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    *(((ubyte_t*) &value) + 3) = *(data++);
    *(((ubyte_t*) &value) + 2) = *(data++);
    *(((ubyte_t*) &value) + 1) = *(data++);
    *(((ubyte_t*) &value) + 0) = *(data++);
}

void NBTTagFloat::write(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    *(data++) = *(((ubyte_t*) &value) + 3);
    *(data++) = *(((ubyte_t*) &value) + 2);
    *(data++) = *(((ubyte_t*) &value) + 1);
    *(data++) = *(((ubyte_t*) &value) + 0);
}

void NBTTagFloat::print(int tab, bool header) {
    NBTTag::print(tab, header);
    std::cout << "TAG_Float(" << (header ? ("'" + name + "'") : "None") << "): " << value << std::endl;
}

float_t NBTTagFloat::get() {
    return value;
}

void NBTTagFloat::set(float_t value) {
    this->value = value;
}

std::shared_ptr<NBTTag> NBTTagFloat::clone() {
    return std::make_shared<NBTTagFloat>(this);
}

bool NBTTagFloat::equals(std::shared_ptr<NBTTag> tag) {
    return tag != nullptr && tag->isFloat() && tag->getName() == name && tag->asFloat()->value == value;
}
