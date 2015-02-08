#ifndef __Serveur__NBTTagByte__
#define __Serveur__NBTTagByte__

#include "NBTTag.h"

class NBTTagByte : public NBTTag {
public:
    NBTTagByte();

    NBTTagByte(NBTTagByte*);

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    int size(bool);

    byte_t get();

    void set(byte_t);

    std::shared_ptr<NBTTag> clone();

    bool equals(std::shared_ptr<NBTTag>);

private:
    byte_t value;
};

#endif /* defined(__Serveur__NBTTagByte__) */
