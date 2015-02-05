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

private:
    //EntityPlayer *player;
    InventoryCrafting craftMatrix;
    InventoryCraftResult craftResult;
};

#endif /* defined(__Serveur__ContainerPlayer__) */
