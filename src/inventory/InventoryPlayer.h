#ifndef __Serveur__InventoryPlayer__
#define __Serveur__InventoryPlayer__

#include "Inventory.h"

class EntityPlayer;

class InventoryPlayer : public Inventory {
public:
    InventoryPlayer(EntityPlayer*);

    std::shared_ptr<ItemStack> getStack();

    std::shared_ptr<ItemStack> getStack(short_t);

    void setStack(std::shared_ptr<ItemStack>);

    void setStack(short_t, std::shared_ptr<ItemStack>);

    int getInventoryStackLimit();

    bool addStack(std::shared_ptr<ItemStack>&);

private:
    std::shared_ptr<ItemStack> main[36];
    std::shared_ptr<ItemStack> armor[4];
    std::shared_ptr<ItemStack> stack;
    short_t currentItem;
    EntityPlayer *player;

    short_t getFirstEmpty();

    int storeItemStack(std::shared_ptr<ItemStack> stack);

    int storePartialItemStack(std::shared_ptr<ItemStack> stack);
};

#endif /* defined(__Serveur__InventoryPlayer__) */
