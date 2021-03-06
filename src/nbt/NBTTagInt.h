#ifndef __Serveur__NBTTagInt__
#define __Serveur__NBTTagInt__

#include "NBTTag.h"

class NBTTagInt : public NBTTag {
public:
    NBTTagInt();

    NBTTagInt(NBTTagInt*);

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    int size(bool);

    int_t get();

    void set(int_t);

    std::shared_ptr<NBTTag> clone();

    bool equals(std::shared_ptr<NBTTag>);

private:
    int_t value;
};

#endif /* defined(__Serveur__NBTTagInt__) */
