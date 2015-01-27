#ifndef __Serveur__NBTTagList__
#define __Serveur__NBTTagList__

#include "NBTTag.h"

#include <iterator>
#include <vector>

class NBTTagList : public NBTTag {
public:
    NBTTagList();

    NBTTagList(NBTTagList*);

    void read(ubyte_t*&, bool);

    void write(ubyte_t*&, bool);

    void print(int, bool);

    std::vector<std::shared_ptr<NBTTag>>::iterator begin();

    std::vector<std::shared_ptr<NBTTag>>::iterator end();

    std::shared_ptr<NBTTag> clone();

    bool equals(std::shared_ptr<NBTTag>);

private:
    std::vector<std::shared_ptr<NBTTag>> children;
};

#endif /* defined(__Serveur__NBTTagList__) */
