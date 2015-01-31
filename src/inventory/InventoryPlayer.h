#ifndef __Serveur__InventoryPlayer__
#define __Serveur__InventoryPlayer__

#include "Inventory.h"
#include "ItemStack.h"

class EntityPlayer;

class InventoryPlayer : public Inventory {
public:
    InventoryPlayer(EntityPlayer*);

    bool addItemStack(std::shared_ptr<ItemStack>);

    std::shared_ptr<ItemStack> getItemStack(int);

    void putItemStack(int, std::shared_ptr<ItemStack>);

    void sendContent();

private:
    std::shared_ptr<ItemStack> slots[45];
    EntityPlayer *player;

    int getFirstEmpty();

    int storeItemStack(std::shared_ptr<ItemStack>);

    int storePartialItemStack(std::shared_ptr<ItemStack>);
};

#endif /* defined(__Serveur__InventoryPlayer__) */
