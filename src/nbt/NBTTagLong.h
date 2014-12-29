#ifndef __Serveur__NBTTagLong__
#define __Serveur__NBTTagLong__

#include "NBTTag.h"

class NBTTagLong : public NBTTag {
public:
    NBTTagLong();

    NBTTagLong(NBTTagLong*);

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    long_t get();

    void set(long_t);

    NBTTagLong *clone();

private:
    long_t value;
};

#endif /* defined(__Serveur__NBTTagLong__) */
