#include "NBTTagByteArray.h"

#include "MathUtils.h"

#include <cstring>

NBTTagByteArray::NBTTagByteArray() : NBTTag(Type::BYTE_ARRAY) {}

NBTTagByteArray::NBTTagByteArray(NBTTagByteArray *tag) : NBTTag(tag), value(tag->value) {}

void NBTTagByteArray::read(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    int_t size;
    *(((ubyte_t*) &size) + 3) = *(data++);
    *(((ubyte_t*) &size) + 2) = *(data++);
    *(((ubyte_t*) &size) + 1) = *(data++);
    *(((ubyte_t*) &size) + 0) = *(data++);
    value = ubytes_t(size);
    std::memcpy(value.data(), data, size);
    data += size;
}

void NBTTagByteArray::write(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    int_t size = value.size();
    *(data++) = *(((ubyte_t*) &size) + 3);
    *(data++) = *(((ubyte_t*) &size) + 2);
    *(data++) = *(((ubyte_t*) &size) + 1);
    *(data++) = *(((ubyte_t*) &size) + 0);
    std::memcpy(data, value.data(), size);
    data += size;
}

void NBTTagByteArray::print(int tab, bool header) {
    NBTTag::print(tab, header);
    std::cout << "TAG_ByteArray(" << (header ? ("'" + name + "'") : "None") << "): [" << std::endl;
    for (int_t i = 0; i < MathUtils::min<int_t>(10, value.size()); i++) {
        if (i > 0)
            std::cout << ", ";
        std::cout << (int) value[i];
    }
    if (value.size() > 10)
        std::cout << "...";
    std::cout << "]" << std::endl;
}

void NBTTagByteArray::get(ubyte_t *dst) {
    std::memcpy(dst, value.data(), value.size());
}

void NBTTagByteArray::set(ubyte_t *frm, int_t size) {
    value = ubytes_t(size);
    std::memcpy(value.data(), frm, size);
}

NBTTagByteArray *NBTTagByteArray::clone() {
    return new NBTTagByteArray(this);
}

bool NBTTagByteArray::equals(NBTTag *tag) {
    return tag->isByteArray() && tag->getName() == name && tag->asByteArray()->value == value;
}
