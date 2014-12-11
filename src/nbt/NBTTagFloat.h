#ifndef __Serveur__NBTTagFloat__
#define __Serveur__NBTTagFloat__

#include "NBTTag.h"

class NBTTagFloat : public NBTTag {
public:
    NBTTagFloat();

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    float_t get();

    void set(float_t);

private:
    float_t value;
};

#endif /* defined(__Serveur__NBTTagFloat__) */
