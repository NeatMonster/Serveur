#include "NBTTagIntArray.h"

#include "MathUtils.h"

#include <cstring>

NBTTagIntArray::NBTTagIntArray() : NBTTag(Type::INT_ARRAY) {}

NBTTagIntArray::NBTTagIntArray(NBTTagIntArray *tag) : NBTTag(tag), value(tag->value) {}

void NBTTagIntArray::read(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    int_t size;
    *(((ubyte_t*) &size) + 3) = *(data++);
    *(((ubyte_t*) &size) + 2) = *(data++);
    *(((ubyte_t*) &size) + 1) = *(data++);
    *(((ubyte_t*) &size) + 0) = *(data++);
    value = ints_t(size);
    for (int_t i = 0; i < size; ++i) {
        *(((ubyte_t*) &value.data()[i]) + 3) = *(data++);
        *(((ubyte_t*) &value.data()[i]) + 2) = *(data++);
        *(((ubyte_t*) &value.data()[i]) + 1) = *(data++);
        *(((ubyte_t*) &value.data()[i]) + 0) = *(data++);
    }
}

void NBTTagIntArray::write(ubyte_t *&data, bool header) {
    NBTTag::read(data, header);
    int_t size = value.size();
    *(data++) = *(((ubyte_t*) &size) + 3);
    *(data++) = *(((ubyte_t*) &size) + 2);
    *(data++) = *(((ubyte_t*) &size) + 1);
    *(data++) = *(((ubyte_t*) &size) + 0);
    for (int_t i = 0; i < size; i++) {
        *(data++) = *(((ubyte_t*) &value.data()[i]) + 3);
        *(data++) = *(((ubyte_t*) &value.data()[i]) + 2);
        *(data++) = *(((ubyte_t*) &value.data()[i]) + 1);
        *(data++) = *(((ubyte_t*) &value.data()[i]) + 0);
    }
    data += 4 * size;
}

void NBTTagIntArray::print(int tab, bool header) {
    NBTTag::print(tab, header);
    std::cout << "TAG_IntArray(" << (header ? ("'" + name + "'") : "None") << "): [";
    for (int_t i = 0; i < MathUtils::min<int_t>(10, value.size()); ++i) {
        if (i > 0)
            std::cout << ", ";
        std::cout << value[i];
    }
    if (value.size() > 10)
        std::cout << "...";
    std::cout << "]" << std::endl;
}

void NBTTagIntArray::get(int_t *dst) {
    std::memcpy(dst, value.data(), 4 * value.size());
}

void NBTTagIntArray::set(int_t *frm, int_t size) {
    value = ints_t(size);
    std::memcpy(value.data(), frm, 4 * size);
}

std::shared_ptr<NBTTag> NBTTagIntArray::clone() {
    return std::make_shared<NBTTagIntArray>(this);
}

bool NBTTagIntArray::equals(std::shared_ptr<NBTTag> tag) {
    return tag != nullptr && tag->isIntArray() && tag->getName() == name && tag->asIntArray()->value == value;
}
