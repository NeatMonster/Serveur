#ifndef __Serveur__Container__
#define __Serveur__Container__

#include "Slot.h"

#include <set>

class EntityPlayer;

class Container {
public:
    static bool canAddItemToSlot(Slot*, std::shared_ptr<ItemStack>);

    static void computeStackSize(std::set<Slot*>, ubyte_t, std::shared_ptr<ItemStack>&, int);

    Container();

    ~Container();

    std::shared_ptr<ItemStack> slotClick(short_t, ubyte_t, ubyte_t, EntityPlayer*);

    void detectAndSendChanges();

    void onCraftGuiOpened(EntityPlayer*);

    void onCraftMatrixChanged(Inventory&);

    Slot *getSlot(short_t);

    std::vector<std::shared_ptr<ItemStack>> getInventory();

    void putStack(short_t, std::shared_ptr<ItemStack>);

protected:
    void addSlot(Slot*);

    void resetDrag();

private:
    std::vector<Slot*> slots;
    std::vector<std::shared_ptr<ItemStack>> stacks;
    byte_t windowId;
    ubyte_t dragMode;
    ubyte_t dragEvent;
    std::set<Slot*> dragSlots;
    std::set<EntityPlayer*> watchers;
};

#endif /* defined(__Serveur__Container__) */
