#ifndef __Serveur__ContainerPlayer__
#define __Serveur__ContainerPlayer__

#include "Container.h"
#include "InventoryCrafting.h"
#include "InventoryCraftResult.h"
#include "InventoryPlayer.h"

class EntityPlayer;

class ContainerPlayer : public Container {
public:
    ContainerPlayer(InventoryPlayer&, EntityPlayer*);

    bool canTakeFromSlot(std::shared_ptr<ItemStack>, Slot*);

    void onContainerClosed(EntityPlayer*);

    void onCraftMatrixChanged(Inventory&);

    std::shared_ptr<ItemStack> transferStackInSlot(EntityPlayer*, short_t);

private:
    //EntityPlayer *player;
    InventoryCrafting craftMatrix;
    InventoryCraftResult craftResult;
};

#endif /* defined(__Serveur__ContainerPlayer__) */
