#ifndef __Serveur__InventoryPlayer__
#define __Serveur__InventoryPlayer__

#include "Inventory.h"

class EntityPlayer;

class InventoryPlayer : public Inventory {
public:
    InventoryPlayer(EntityPlayer*);

    std::shared_ptr<ItemStack> getCursor();

    void setCursor(std::shared_ptr<ItemStack>);

    std::shared_ptr<ItemStack> getStack(short_t);

    void setStack(short_t, std::shared_ptr<ItemStack>);

    std::shared_ptr<ItemStack> decrStackSize(short_t, int);

    short_t getFirstEmpty();

    int getInventoryStackLimit();

    bool addStack(std::shared_ptr<ItemStack>&);

private:
    std::shared_ptr<ItemStack> main[36];
    std::shared_ptr<ItemStack> armor[4];
    std::shared_ptr<ItemStack> cursor;
    //short_t currentItem;
    EntityPlayer *player;

    int storeItemStack(std::shared_ptr<ItemStack> stack);

    int storePartialItemStack(std::shared_ptr<ItemStack> stack);
};

#endif /* defined(__Serveur__InventoryPlayer__) */
