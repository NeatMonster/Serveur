#include "NBTTagInt.h"

NBTTagInt::NBTTagInt() : NBTTag(Type::INT) {}

NBTTagInt::NBTTagInt(NBTTagInt *tag) : NBTTag(tag), value(tag->value) {}

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

int NBTTagInt::size(bool header) {
    return NBTTag::size(header) + 4;
}

int_t NBTTagInt::get() {
    return value;
}

void NBTTagInt::set(int_t value) {
    this->value = value;
}

std::shared_ptr<NBTTag> NBTTagInt::clone() {
    return std::make_shared<NBTTagInt>(this);
}

bool NBTTagInt::equals(std::shared_ptr<NBTTag> tag) {
    return tag != nullptr && tag->isInt() && tag->getName() == name && tag->asInt()->value == value;
}
