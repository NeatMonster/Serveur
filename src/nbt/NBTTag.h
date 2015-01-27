#ifndef __Serveur__NBTTag__
#define __Serveur__NBTTag__

#include "Types.h"

#include <stdexcept>

class NBTTagByte;
class NBTTagByteArray;
class NBTTagCompound;
class NBTTagDouble;
class NBTTagFloat;
class NBTTagInt;
class NBTTagIntArray;
class NBTTagList;
class NBTTagLong;
class NBTTagShort;
class NBTTagString;

class NBTTag : public std::enable_shared_from_this<NBTTag> {
    friend class NBTTagCompound;
    friend class NBTTagList;

public:
    enum Type { END, BYTE, SHORT, INT, LONG, FLOAT, DOUBLE, BYTE_ARRAY, STRING, LIST, COMPOUND, INT_ARRAY };

    struct NBTException : public std::runtime_error {
        NBTException(string_t s) : std::runtime_error(s) {}
    };

    NBTTag(Type);

    NBTTag(NBTTag*);

    virtual ~NBTTag();

    static std::shared_ptr<NBTTag> read(ubyte_t*&);

    void write(ubyte_t*&);

    void print();

    string_t getName();

    bool isByte();

    std::shared_ptr<NBTTagByte> asByte();

    bool isByteArray();

    std::shared_ptr<NBTTagByteArray> asByteArray();

    bool isCompound();

    std::shared_ptr<NBTTagCompound> asCompound();

    bool isDouble();

    std::shared_ptr<NBTTagDouble> asDouble();

    bool isFloat();

    std::shared_ptr<NBTTagFloat> asFloat();

    bool isInt();

    std::shared_ptr<NBTTagInt> asInt();

    bool isIntArray();

    std::shared_ptr<NBTTagIntArray> asIntArray();

    bool isList();

    std::shared_ptr<NBTTagList> asList();

    bool isLong();

    std::shared_ptr<NBTTagLong> asLong();

    bool isShort();

    std::shared_ptr<NBTTagShort> asShort();

    bool isString();

    std::shared_ptr<NBTTagString> asString();

    virtual std::shared_ptr<NBTTag> clone() = 0;

    virtual bool equals(std::shared_ptr<NBTTag>) = 0;

protected:
    Type type;
    string_t name;

    static std::shared_ptr<NBTTag> read(ubyte_t*&, Type, bool);

    virtual void read(ubyte_t*&, bool);

    virtual void write(ubyte_t*&, bool);

    virtual void print(int, bool);
};

#endif /* defined(__Serveur__NBTTag__) */
