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

    std::shared_ptr<NBTTag> clone();

    bool equals(std::shared_ptr<NBTTag>);

private:
    float_t value;
};

#endif /* defined(__Serveur__NBTTagFloat__) */
