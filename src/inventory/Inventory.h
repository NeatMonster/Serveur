#ifndef __Serveur__Inventory__
#define __Serveur__Inventory__

#include "Types.h"

class ItemStack;

class Inventory {
public:
    Inventory();

    virtual std::shared_ptr<ItemStack> getItemStack(int) = 0;

    virtual void putItemStack(int, std::shared_ptr<ItemStack>) = 0;
};

#endif /* defined(__Serveur__Inventory__) */
