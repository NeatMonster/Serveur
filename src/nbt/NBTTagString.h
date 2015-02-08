#ifndef __Serveur__NBTTagString__
#define __Serveur__NBTTagString__

#include "NBTTag.h"

class NBTTagString : public NBTTag {
public:
    NBTTagString();

    NBTTagString(NBTTagString*);

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    int size(bool);

    string_t get();

    void set(string_t);

    std::shared_ptr<NBTTag> clone();

    bool equals(std::shared_ptr<NBTTag>);

private:
    string_t value;
};

#endif /* defined(__Serveur__NBTTagString__) */
