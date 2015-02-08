#include "NBTTagString.h"

#include <cstring>

NBTTagString::NBTTagString() : NBTTag(Type::STRING) {}

NBTTagString::NBTTagString(NBTTagString *tag) : NBTTag(tag), value(tag->value) {}

void NBTTagString::read(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    ushort_t size;
    *(((ubyte_t*) &size) + 1) = *(data++);
    *(((ubyte_t*) &size) + 0) = *(data++);
    if (size > 0)
        value = string_t((char*) data, size);
    data += size;
}

void NBTTagString::write(ubyte_t *&data, bool header) {
    NBTTag::write(data, header);
    ushort_t size = value.size();
    *(data++) = *(((ubyte_t*) &size) + 1);
    *(data++) = *(((ubyte_t*) &size) + 0);
    if (size > 0)
        std::memcpy(data, value.data(), size);
    data += size;
}

void NBTTagString::print(int tab, bool header) {
    NBTTag::print(tab, header);
    std::cout << "TAG_String(" << (header ? ("'" + name + "'") : "None") << "): '" << value << "'" << std::endl;
}

int NBTTagString::size(bool header) {
    return NBTTag::size(header) + 2 + value.size();
}

string_t NBTTagString::get() {
    return value;
}

void NBTTagString::set(string_t value) {
    this->value = value;
}

std::shared_ptr<NBTTag> NBTTagString::clone() {
    return std::make_shared<NBTTagString>(this);
}

bool NBTTagString::equals(std::shared_ptr<NBTTag> tag) {
    return tag != nullptr && tag->isString() && tag->getName() == name && tag->asString()->value == value;
}
