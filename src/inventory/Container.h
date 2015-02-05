#ifndef __Serveur__Container__
#define __Serveur__Container__

#include "Slot.h"

#include <set>

class EntityPlayer;

class Container {
public:
    Container();

    ~Container();

    void detectAndSendChanges();

    void onCraftGuiOpened(EntityPlayer*);

    void onCraftMatrixChanged(Inventory&);

    Slot *getSlot(short_t);

    std::vector<std::shared_ptr<ItemStack>> getInventory();

    void putStack(short_t, std::shared_ptr<ItemStack>);

protected:
    void addSlot(Slot*);

private:
    std::vector<Slot*> slots;
    std::vector<std::shared_ptr<ItemStack>> stacks;
    byte_t windowId;
    //ubyte_t dragMode;
    //ubyte_t dragEvent;
    //std::vector<Slot*> dragSlots;
    std::set<EntityPlayer*> watchers;
};

#endif /* defined(__Serveur__Container__) */
