#ifndef __Serveur__NBTTagDouble__
#define __Serveur__NBTTagDouble__

#include "NBTTag.h"

class NBTTagDouble : public NBTTag {
public:
    NBTTagDouble();

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    double_t get();

    void set(double_t);

private:
    double_t value;
};

#endif /* defined(__Serveur__NBTTagDouble__) */