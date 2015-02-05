#ifndef __Serveur__SlotCrafting__
#define __Serveur__SlotCrafting__

#include "EntityPlayer.h"
#include "InventoryCrafting.h"
#include "Slot.h"

class SlotCrafting : public Slot {
public:
    SlotCrafting(EntityPlayer*, InventoryCrafting&, Inventory&, short_t);

private:
    EntityPlayer *player;
    InventoryCrafting &craftMatrix;
};

#endif /* defined(__Serveur__SlotCrafting__) */
