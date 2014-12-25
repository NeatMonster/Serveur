#ifndef __Serveur__Slot__
#define __Serveur__Slot__

#include "ItemStack.h"

class Slot {
public:
    Slot();

    ItemStack *getStack();

    void setStack(ItemStack*);

private:
    ItemStack *stack;
};

#endif /* defined(__Serveur__Slot__) */
