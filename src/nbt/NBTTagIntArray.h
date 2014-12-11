#ifndef __Serveur__NBTTagIntArray__
#define __Serveur__NBTTagIntArray__

#include "NBTTag.h"

class NBTTagIntArray : public NBTTag {
public:
    NBTTagIntArray();

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    void get(int_t*);

    void set(int_t*, int_t);

private:
    ints_t value;
};

#endif /* defined(__Serveur__NBTTagIntArray__) */
