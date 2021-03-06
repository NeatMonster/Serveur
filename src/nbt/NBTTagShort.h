#ifndef __Serveur__NBTTagShort__
#define __Serveur__NBTTagShort__

#include "NBTTag.h"

class NBTTagShort : public NBTTag {
public:
    NBTTagShort();

    NBTTagShort(NBTTagShort*);

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    int size(bool);

    short_t get();

    void set(short_t);

    std::shared_ptr<NBTTag> clone();

    bool equals(std::shared_ptr<NBTTag>);

private:
    short_t value;
};

#endif /* defined(__Serveur__NBTTagShort__) */
