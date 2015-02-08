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

    int size(bool);

    long_t get();

    void set(long_t);

    std::shared_ptr<NBTTag> clone();

    bool equals(std::shared_ptr<NBTTag>);

private:
    long_t value;
};

#endif /* defined(__Serveur__NBTTagLong__) */
