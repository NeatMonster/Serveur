#include "NBTTag.h"

#include "NBTTagByte.h"
#include "NBTTagByteArray.h"
#include "NBTTagCompound.h"
#include "NBTTagDouble.h"
#include "NBTTagFloat.h"
#include "NBTTagInt.h"
#include "NBTTagIntArray.h"
#include "NBTTagList.h"
#include "NBTTagLong.h"
#include "NBTTagShort.h"
#include "NBTTagString.h"

#include <cassert>
#include <cstring>

NBTTag::NBTTag(Type type) : type(type) {}

NBTTag::~NBTTag() {}

NBTTag *NBTTag::read(ubyte_t *&data) {
    Type type = (Type) *(data++);
    return NBTTag::read(data, type, true);
}

void NBTTag::write(ubyte_t *&data) {
    write(data, true);
}

void NBTTag::print() {
    print(0, true);
}

bool NBTTag::isByte() {
    return type == NBTTag::Type::BYTE;
}

NBTTagByte *NBTTag::asByte() {
    return (NBTTagByte*) this;
}

bool NBTTag::isByteArray() {
    return type == NBTTag::Type::BYTE_ARRAY;
}

NBTTagByteArray *NBTTag::asByteArray() {
    return (NBTTagByteArray*) this;
}

bool NBTTag::isCompound() {
    return type == NBTTag::Type::COMPOUND;
}

NBTTagCompound *NBTTag::asCompound() {
    return (NBTTagCompound*) this;
}

bool NBTTag::isDouble() {
    return type == NBTTag::Type::DOUBLE;
}

NBTTagDouble *NBTTag::asDouble() {
    return (NBTTagDouble*) this;
}

bool NBTTag::isFloat() {
    return type == NBTTag::Type::FLOAT;
}

NBTTagFloat *NBTTag::asFloat() {
    return (NBTTagFloat*) this;
}

bool NBTTag::isInt() {
    return type == NBTTag::Type::INT;
}

NBTTagInt *NBTTag::asInt() {
    return (NBTTagInt*) this;
}

bool NBTTag::isIntArray() {
    return type == NBTTag::Type::INT_ARRAY;
}

NBTTagIntArray *NBTTag::asIntArray() {
    return (NBTTagIntArray*) this;
}

bool NBTTag::isList() {
    return type == NBTTag::Type::LIST;
}

NBTTagList *NBTTag::asList() {
    return (NBTTagList*) this;
}

bool NBTTag::isLong() {
    return type == NBTTag::Type::LONG;
}

NBTTagLong *NBTTag::asLong() {
    return (NBTTagLong*) this;
}

bool NBTTag::isShort() {
    return type == NBTTag::Type::SHORT;
}

NBTTagShort *NBTTag::asShort() {
    return (NBTTagShort*) this;
}

bool NBTTag::isString() {
    return type == NBTTag::Type::STRING;
}

NBTTagString *NBTTag::asString() {
    return (NBTTagString*) this;
}

NBTTag *NBTTag::read(ubyte_t *&data, Type type, bool header) {
    NBTTag *tag = nullptr;
    switch (type) {
        case NBTTag::Type::END:
            return nullptr;
        case NBTTag::Type::BYTE:
            tag = new NBTTagByte();
            break;
        case NBTTag::Type::SHORT:
            tag = new NBTTagShort();
            break;
        case NBTTag::Type::INT:
            tag = new NBTTagInt();
            break;
        case NBTTag::Type::LONG:
            tag = new NBTTagLong();
            break;
        case NBTTag::Type::FLOAT:
            tag = new NBTTagFloat();
            break;
        case NBTTag::Type::DOUBLE:
            tag = new NBTTagDouble();
            break;
        case NBTTag::Type::BYTE_ARRAY:
            tag = new NBTTagByteArray();
            break;
        case NBTTag::Type::STRING:
            tag = new NBTTagString();
            break;
        case NBTTag::Type::LIST:
            tag = new NBTTagList();
            break;
        case NBTTag::Type::COMPOUND:
            tag = new NBTTagCompound();
            break;
        case NBTTag::Type::INT_ARRAY:
            tag = new NBTTagIntArray();
            break;
        default:
            assert(false);
            break;
    }
    tag->read(data, header);
    return tag;
}

void NBTTag::read(ubyte_t *&data, bool header) {
    if (header) {
        ushort_t size;
        *(((ubyte_t*) &size) + 1) = *(data++);
        *(((ubyte_t*) &size) + 0) = *(data++);
        if (size > 0)
            name = string_t((char*) data, size);
        data += size;
    }
}

void NBTTag::write(ubyte_t *&data, bool header) {
    if (header) {
        *(data++) = type;
        ushort_t size = name.size();
        *(data++) = *(((ubyte_t*) &size) + 1);
        *(data++) = *(((ubyte_t*) &size) + 0);
        if (size > 0)
            memcpy(data, name.data(), size);
        data += size;
    }
}

void NBTTag::print(int tab, bool) {
    for (int i = 0; i < 2 * tab; i++)
        std::cout << " ";
}
