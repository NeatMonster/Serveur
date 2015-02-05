#ifndef __Serveur__Slot__
#define __Serveur__Slot__

#include "Inventory.h"
#include "ItemStack.h"

class Slot {
public:
    short_t slotNumber;

    Slot(Inventory&, short_t);

    virtual ~Slot();

    bool hasStack();

    std::shared_ptr<ItemStack> getStack();

    void setStack(std::shared_ptr<ItemStack>);

    virtual bool isValid(std::shared_ptr<ItemStack>);

    virtual int getSlotMaxSize(std::shared_ptr<ItemStack>);

    virtual int getSlotStackLimit();

private:
    Inventory &inventory;
    short_t slotIndex;

};

#endif /* defined(__Serveur__Slot__) */
