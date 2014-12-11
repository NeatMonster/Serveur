#ifndef __Serveur__NBTTag__
#define __Serveur__NBTTag__

#include "Types.h"

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

class NBTTag {
    friend class NBTTagCompound;
    friend class NBTTagList;

public:
    enum Type { END, BYTE, SHORT, INT, LONG, FLOAT, DOUBLE, BYTE_ARRAY, STRING, LIST, COMPOUND, INT_ARRAY };

    NBTTag(Type);

    virtual ~NBTTag();

    static NBTTag *read(ubyte_t*&);

    void write(ubyte_t*&);

    void print();

    bool isByte();

    NBTTagByte *asByte();

    bool isByteArray();

    NBTTagByteArray *asByteArray();

    bool isCompound();

    NBTTagCompound *asCompound();

    bool isDouble();

    NBTTagDouble *asDouble();

    bool isFloat();

    NBTTagFloat *asFloat();

    bool isInt();

    NBTTagInt *asInt();

    bool isIntArray();

    NBTTagIntArray *asIntArray();

    bool isList();

    NBTTagList *asList();

    bool isLong();

    NBTTagLong *asLong();

    bool isShort();

    NBTTagShort *asShort();

    bool isString();

    NBTTagString *asString();

protected:
    Type type;
    string_t name;

    static NBTTag *read(ubyte_t*&, Type, bool);

    virtual void read(ubyte_t*&, bool);

    virtual void write(ubyte_t*&, bool);

    virtual void print(int, bool);
};

#endif /* defined(__Serveur__NBTTag__) */
