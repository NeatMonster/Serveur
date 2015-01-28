#ifndef __Serveur__ItemBlock__
#define __Serveur__ItemBlock__

#include "Item.h"

class Block;

class ItemBlock : public Item {
public:
    ItemBlock(Block*);

    Block *getBlock();

private:
    Block *block;
};

#endif /* defined(__Serveur__ItemBlock__) */
