#ifndef __Serveur__Slot__
#define __Serveur__Slot__

#include "Inventory.h"
#include "ItemStack.h"

class EntityPlayer;

class Slot {
public:
    Inventory &inventory;
    short_t slotNumber;

    Slot(Inventory&, short_t);

    virtual ~Slot();

    bool hasStack();

    std::shared_ptr<ItemStack> getStack();

    void putStack(std::shared_ptr<ItemStack>);

    void onSlotChange(std::shared_ptr<ItemStack>, std::shared_ptr<ItemStack>);

    virtual bool canTakeStack(EntityPlayer*);

    virtual std::shared_ptr<ItemStack> decrStackSize(count_t);

    virtual bool isValid(std::shared_ptr<ItemStack>);

    virtual count_t getSlotMaxSize(std::shared_ptr<ItemStack>);

    virtual count_t getSlotStackLimit();

    virtual void onPickupFromSlot(EntityPlayer*, std::shared_ptr<ItemStack>);

protected:
    virtual void onCrafting(std::shared_ptr<ItemStack>);

    virtual void onCrafting(std::shared_ptr<ItemStack>, count_t);

private:
    short_t slotIndex;
};

#endif /* defined(__Serveur__Slot__) */
