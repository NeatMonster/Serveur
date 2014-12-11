#ifndef __Serveur__NBTTagInt__
#define __Serveur__NBTTagInt__

#include "NBTTag.h"

class NBTTagInt : public NBTTag {
public:
    NBTTagInt();

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    int_t get();

    void set(int_t);

private:
    int_t value;
};

#endif /* defined(__Serveur__NBTTagInt__) */
