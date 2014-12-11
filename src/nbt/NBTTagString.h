#ifndef __Serveur__NBTTagString__
#define __Serveur__NBTTagString__

#include "NBTTag.h"

class NBTTagString : public NBTTag {
public:
    NBTTagString();

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    string_t get();

    void set(string_t);

private:
    string_t value;
};

#endif /* defined(__Serveur__NBTTagString__) */
