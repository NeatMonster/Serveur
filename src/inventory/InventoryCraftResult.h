#ifndef __Serveur__InventoryCraftResult__
#define __Serveur__InventoryCraftResult__

#include "Inventory.h"

class InventoryCraftResult : public Inventory {
public:
    std::shared_ptr<ItemStack> getStack(short_t);

    void setStack(short_t, std::shared_ptr<ItemStack>);

    int getInventoryStackLimit();

private:
    std::shared_ptr<ItemStack> stack;
};

#endif /* defined(__Serveur__InventoryCraftResult__) */
