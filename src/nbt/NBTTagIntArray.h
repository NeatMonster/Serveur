#ifndef __Serveur__NBTTagIntArray__
#define __Serveur__NBTTagIntArray__

#include "NBTTag.h"

class NBTTagIntArray : public NBTTag {
public:
    NBTTagIntArray();

    NBTTagIntArray(NBTTagIntArray*);

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    void get(int_t*);

    void set(int_t*, int_t);

    std::shared_ptr<NBTTag> clone();

    bool equals(std::shared_ptr<NBTTag>);

private:
    ints_t value;
};

#endif /* defined(__Serveur__NBTTagIntArray__) */
