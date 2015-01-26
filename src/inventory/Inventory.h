#ifndef __Serveur__Inventory__
#define __Serveur__Inventory__

#include "ItemStack.h"

#include "Slot.h"
#include "Types.h"

class Inventory {
public:
    Inventory();

    virtual ~Inventory();

    void putStack(short_t, std::shared_ptr<ItemStack>);

protected:
    void addSlot(Slot*);

    Slot *getSlot(short_t);

private:
    std::vector<Slot*> slots;
};

#endif /* defined(__Serveur__Inventory__) */
