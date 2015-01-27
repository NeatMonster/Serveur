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

#include <cstring>

NBTTag::NBTTag(Type type) : type(type) {}

NBTTag::NBTTag(NBTTag *tag) : type(tag->type), name(tag->name) {}

NBTTag::~NBTTag() {}

std::shared_ptr<NBTTagCompound> NBTTag::read(ubyte_t *&data) {
    Type type = (Type) *(data++);
    return std::dynamic_pointer_cast<NBTTagCompound>(NBTTag::read(data, type, true));
}

void NBTTag::write(ubyte_t *&data) {
    write(data, true);
}

void NBTTag::print() {
    print(0, true);
}

string_t NBTTag::getName() {
    return name;
}

bool NBTTag::isByte() {
    return type == NBTTag::Type::BYTE;
}

std::shared_ptr<NBTTagByte> NBTTag::asByte() {
    return std::dynamic_pointer_cast<NBTTagByte>(shared_from_this());
}

bool NBTTag::isByteArray() {
    return type == NBTTag::Type::BYTE_ARRAY;
}

std::shared_ptr<NBTTagByteArray> NBTTag::asByteArray() {
    return std::dynamic_pointer_cast<NBTTagByteArray>(shared_from_this());
}

bool NBTTag::isCompound() {
    return type == NBTTag::Type::COMPOUND;
}

std::shared_ptr<NBTTagCompound> NBTTag::asCompound() {
    return std::dynamic_pointer_cast<NBTTagCompound>(shared_from_this());
}

bool NBTTag::isDouble() {
    return type == NBTTag::Type::DOUBLE;
}

std::shared_ptr<NBTTagDouble> NBTTag::asDouble() {
    return std::dynamic_pointer_cast<NBTTagDouble>(shared_from_this());
}

bool NBTTag::isFloat() {
    return type == NBTTag::Type::FLOAT;
}

std::shared_ptr<NBTTagFloat> NBTTag::asFloat() {
    return std::dynamic_pointer_cast<NBTTagFloat>(shared_from_this());
}

bool NBTTag::isInt() {
    return type == NBTTag::Type::INT;
}

std::shared_ptr<NBTTagInt> NBTTag::asInt() {
    return std::dynamic_pointer_cast<NBTTagInt>(shared_from_this());
}

bool NBTTag::isIntArray() {
    return type == NBTTag::Type::INT_ARRAY;
}

std::shared_ptr<NBTTagIntArray> NBTTag::asIntArray() {
    return std::dynamic_pointer_cast<NBTTagIntArray>(shared_from_this());
}

bool NBTTag::isList() {
    return type == NBTTag::Type::LIST;
}

std::shared_ptr<NBTTagList> NBTTag::asList() {
    return std::dynamic_pointer_cast<NBTTagList>(shared_from_this());
}

bool NBTTag::isLong() {
    return type == NBTTag::Type::LONG;
}

std::shared_ptr<NBTTagLong> NBTTag::asLong() {
    return std::dynamic_pointer_cast<NBTTagLong>(shared_from_this());
}

bool NBTTag::isShort() {
    return type == NBTTag::Type::SHORT;
}

std::shared_ptr<NBTTagShort> NBTTag::asShort() {
    return std::dynamic_pointer_cast<NBTTagShort>(shared_from_this());
}

bool NBTTag::isString() {
    return type == NBTTag::Type::STRING;
}

std::shared_ptr<NBTTagString> NBTTag::asString() {
    return std::dynamic_pointer_cast<NBTTagString>(shared_from_this());
}

std::shared_ptr<NBTTag> NBTTag::read(ubyte_t *&data, Type type, bool header) {
    std::shared_ptr<NBTTag> tag;
    switch (type) {
        case NBTTag::Type::END:
            return nullptr;
        case NBTTag::Type::BYTE:
            tag = std::make_shared<NBTTagByte>();
            break;
        case NBTTag::Type::SHORT:
            tag = std::make_shared<NBTTagShort>();
            break;
        case NBTTag::Type::INT:
            tag = std::make_shared<NBTTagInt>();
            break;
        case NBTTag::Type::LONG:
            tag = std::make_shared<NBTTagLong>();
            break;
        case NBTTag::Type::FLOAT:
            tag = std::make_shared<NBTTagFloat>();
            break;
        case NBTTag::Type::DOUBLE:
            tag = std::make_shared<NBTTagDouble>();
            break;
        case NBTTag::Type::BYTE_ARRAY:
            tag = std::make_shared<NBTTagByteArray>();
            break;
        case NBTTag::Type::STRING:
            tag = std::make_shared<NBTTagString>();
            break;
        case NBTTag::Type::LIST:
            tag = std::make_shared<NBTTagList>();
            break;
        case NBTTag::Type::COMPOUND:
            tag = std::make_shared<NBTTagCompound>();
            break;
        case NBTTag::Type::INT_ARRAY:
            tag = std::make_shared<NBTTagIntArray>();
            break;
        default:
            throw NBTException("Type inconnu : " + std::to_string(type));
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
            std::memcpy(data, name.data(), size);
        data += size;
    }
}

void NBTTag::print(int tab, bool) {
    for (int i = 0; i < 2 * tab; i++)
        std::cout << " ";
}
