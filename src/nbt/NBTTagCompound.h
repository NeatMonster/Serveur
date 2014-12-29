#ifndef __Serveur__NBTTagCompound__
#define __Serveur__NBTTagCompound__

#include "NBTTag.h"
#include <unordered_map>

class NBTTagCompound : public NBTTag {
public:
    NBTTagCompound();

    NBTTagCompound(NBTTagCompound*);

    ~NBTTagCompound();

    void read(ubyte_t *&, bool);

    void write(ubyte_t *&, bool);

    void print(int, bool);

    NBTTag *&get(string_t);

    void set(string_t, NBTTag*&);

    NBTTagCompound *clone();

private:
    std::unordered_map<string_t, NBTTag*> children;
};

#endif /* defined(__Serveur__NBTTagCompound__) */
