#ifndef __Serveur__InventoryCrafting__
#define __Serveur__InventoryCrafting__

#include "Container.h"
#include "Inventory.h"

class InventoryCrafting : public Inventory {
public:
    InventoryCrafting(Container&, int);

    std::shared_ptr<ItemStack> getStack(short_t);

    void setStack(short_t, std::shared_ptr<ItemStack>);

    std::shared_ptr<ItemStack> decrStackSize(short_t, int);

    int getInventoryStackLimit();

private:
    std::vector<std::shared_ptr<ItemStack>> stacks;
    Container &eventHandler;
};

#endif /* defined(__Serveur__InventoryCrafting__) */
