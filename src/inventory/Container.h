#ifndef __Serveur__Container__
#define __Serveur__Container__

#include "Slot.h"

#include <set>

class EntityPlayer;

class Container {
public:
    static bool canAddItemToSlot(Slot*, std::shared_ptr<ItemStack>);

    static void computeStackSize(std::set<Slot*>, ubyte_t, std::shared_ptr<ItemStack>, count_t);

    Container();

    ~Container();

    byte_t getWindowId();

    std::shared_ptr<ItemStack> slotClick(short_t, ubyte_t, ubyte_t, EntityPlayer*);

    bool canCraft(EntityPlayer*);

    void setCanCraft(EntityPlayer*, bool);

    void detectAndSendChanges();

    void detectAndSendChanges(EntityPlayer*);

    virtual void onContainerClosed(EntityPlayer*);

    void onCraftGuiOpened(EntityPlayer*);

    void onCraftMatrixChanged(Inventory&);

    Slot *getSlot(short_t);

    std::vector<std::shared_ptr<ItemStack>> getInventory();

    void putStack(short_t, std::shared_ptr<ItemStack>);

    void sendContainer(EntityPlayer*);

    virtual std::shared_ptr<ItemStack> transferStackInSlot(EntityPlayer*, short_t);

protected:
    void addSlot(Slot*);

    virtual bool canTakeFromSlot(std::shared_ptr<ItemStack>, Slot*);

    bool mergeItemStack(std::shared_ptr<ItemStack>, short_t, short_t, bool);

    void resetDrag();

private:
    std::vector<Slot*> slots;
    std::vector<std::shared_ptr<ItemStack>> stacks;
    byte_t windowId;
    ubyte_t dragMode;
    ubyte_t dragEvent;
    std::set<Slot*> dragSlots;
    std::set<EntityPlayer*> crafters;
    std::set<EntityPlayer*> watchers;
};

#endif /* defined(__Serveur__Container__) */
