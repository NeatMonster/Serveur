#ifndef __Serveur__NBTTagByteArray__
#define __Serveur__NBTTagByteArray__

#include "NBTTag.h"

class NBTTagByteArray : public NBTTag {
public:
    NBTTagByteArray();

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    void get(ubyte_t*);

    void set(ubyte_t*, int_t);

private:
    ubytes_t value;
};

#endif /* defined(__Serveur__NBTTagByteArray__) */