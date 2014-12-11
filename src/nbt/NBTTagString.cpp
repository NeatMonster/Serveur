#include "NBTTagString.h"

NBTTagString::NBTTagString() : NBTTag(Type::STRING) {}

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
        memcpy(data, value.data(), size);
    data += size;
}

void NBTTagString::print(int tab, bool header) {
    NBTTag::print(tab, header);
    std::cout << "TAG_String(" << (header ? ("'" + name + "'") : "None") << "): '" << value << "'" << std::endl;
}

string_t NBTTagString::get() {
    return value;
}

void NBTTagString::set(string_t value) {
    this->value = value;
}
