#ifndef __Serveur__Slot__
#define __Serveur__Slot__

#include "Inventory.h"
#include "ItemStack.h"

class Slot {
public:
    short_t slotNumber;

    Slot(Inventory&, short_t);

    virtual ~Slot();

    virtual std::shared_ptr<ItemStack> getStack();

    virtual void setStack(std::shared_ptr<ItemStack>);

private:
    Inventory &inventory;
    short_t slotIndex;

};

#endif /* defined(__Serveur__Slot__) */
