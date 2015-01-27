#ifndef __Serveur__NBTTagCompound__
#define __Serveur__NBTTagCompound__

#include "NBTTag.h"
#include <unordered_map>

class NBTTagCompound : public NBTTag {
public:
    NBTTagCompound();

    NBTTagCompound(NBTTagCompound*);

    void read(ubyte_t *&, bool);

    void write(ubyte_t *&, bool);

    void print(int, bool);

    std::shared_ptr<NBTTag> get(string_t);

    void set(string_t, std::shared_ptr<NBTTag>);

    std::shared_ptr<NBTTag> clone();

    bool equals(std::shared_ptr<NBTTag>);

private:
    std::unordered_map<string_t, std::shared_ptr<NBTTag>> children;
};

#endif /* defined(__Serveur__NBTTagCompound__) */
