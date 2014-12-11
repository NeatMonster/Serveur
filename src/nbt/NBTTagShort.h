#ifndef __Serveur__NBTTagShort__
#define __Serveur__NBTTagShort__

#include "NBTTag.h"

class NBTTagShort : public NBTTag {
public:
    NBTTagShort();

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    short_t get();

    void set(short_t);

private:
    short_t value;
};

#endif /* defined(__Serveur__NBTTagShort__) */
