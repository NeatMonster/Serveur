#ifndef __Serveur__Slot__
#define __Serveur__Slot__

#include "ItemStack.h"

class Slot {
public:
    Slot();

    std::shared_ptr<ItemStack> getStack();

    void setStack(std::shared_ptr<ItemStack>);

private:
    std::shared_ptr<ItemStack> stack;
};

#endif /* defined(__Serveur__Slot__) */
