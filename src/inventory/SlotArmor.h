#ifndef __Serveur__SlotArmor__
#define __Serveur__SlotArmor__

#include "Slot.h"

class SlotArmor : public Slot {
public:
    SlotArmor(Inventory&, short_t);

    bool isValid(std::shared_ptr<ItemStack>);

    count_t getSlotStackLimit();
};

#endif /* defined(__Serveur__SlotArmor__) */
