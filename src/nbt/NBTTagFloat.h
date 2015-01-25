#ifndef __Serveur__NBTTagFloat__
#define __Serveur__NBTTagFloat__

#include "NBTTag.h"

class NBTTagFloat : public NBTTag {
public:
    NBTTagFloat();

    NBTTagFloat(NBTTagFloat*);

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    float_t get();

    void set(float_t);

    NBTTagFloat *clone();

    bool equals(NBTTag*);

private:
    float_t value;
};

#endif /* defined(__Serveur__NBTTagFloat__) */
