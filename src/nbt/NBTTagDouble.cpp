#include "NBTTagDouble.h"

NBTTagDouble::NBTTagDouble() : NBTTag(Type::DOUBLE) {}

NBTTagDouble::NBTTagDouble(NBTTagDouble *tag) : NBTTag(tag), value(tag->value) {}

void NBTTagDouble::read(ubyte_t *&data, bool header) {
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

void NBTTagDouble::write(ubyte_t *&data, bool header) {
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

void NBTTagDouble::print(int tab, bool header) {
    NBTTag::print(tab, header);
    std::cout << "TAG_Double(" << (header ? ("'" + name + "'") : "None") << "): " << value << std::endl;
}

int NBTTagDouble::size(bool header) {
    return NBTTag::size(header) + 8;
}

double_t NBTTagDouble::get() {
    return value;
}

void NBTTagDouble::set(double_t value) {
    this->value = value;
}

std::shared_ptr<NBTTag> NBTTagDouble::clone() {
    return std::make_shared<NBTTagDouble>(this);
}

bool NBTTagDouble::equals(std::shared_ptr<NBTTag> tag) {
    return tag != nullptr && tag->isDouble() && tag->getName() == name && tag->asDouble()->value == value;
}
