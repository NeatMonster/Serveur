#ifndef __Serveur__Inventory__
#define __Serveur__Inventory__

#include "ItemStack.h"

class Inventory {
public:
    virtual std::shared_ptr<ItemStack> getStack(short_t) = 0;

    virtual void setStack(short_t, std::shared_ptr<ItemStack>) = 0;

    virtual std::shared_ptr<ItemStack> decrStackSize(short_t, int);

    virtual int getInventoryStackLimit() = 0;
};

#endif /* defined(__Serveur__Inventory__) */
