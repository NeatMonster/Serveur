#ifndef __Serveur__NBTTagList__
#define __Serveur__NBTTagList__

#include "NBTTag.h"

#include <iterator>
#include <vector>

class NBTTagList : public NBTTag {
public:
    NBTTagList();

    NBTTagList(NBTTagList*);

    ~NBTTagList();

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    std::vector<NBTTag*>::iterator begin();

    std::vector<NBTTag*>::iterator end();

    NBTTagList *clone();

private:
    std::vector<NBTTag*> children;
};

#endif /* defined(__Serveur__NBTTagList__) */
