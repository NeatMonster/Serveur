#ifndef __Serveur__InventoryCrafting__
#define __Serveur__InventoryCrafting__

#include "Inventory.h"

class InventoryCrafting : public Inventory {
public:
    InventoryCrafting(int);

    std::shared_ptr<ItemStack> getStack(short_t);

    void setStack(short_t, std::shared_ptr<ItemStack>);

    int getInventoryStackLimit();

private:
    std::vector<std::shared_ptr<ItemStack>> stacks;
};

#endif /* defined(__Serveur__InventoryCrafting__) */
