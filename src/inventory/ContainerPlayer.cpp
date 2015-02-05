#include "ContainerPlayer.h"

#include "Slot.h"
#include "SlotArmor.h"
#include "SlotCrafting.h"

ContainerPlayer::ContainerPlayer(InventoryPlayer &inventory, EntityPlayer *player) : /*player(player),*/ craftMatrix(2) {
    addSlot(new SlotCrafting(player, craftMatrix, craftResult, 0));
    for (short_t index = 0; index < 4; ++index)
        addSlot(new Slot(craftMatrix, index));
    for (short_t index = 0; index < 4; ++index)
        addSlot(new SlotArmor(craftMatrix, 39 - index));
    for (short_t index = 9; index < 36; ++index)
        addSlot(new Slot(inventory, index));
    for (short_t index = 0; index < 9; ++index)
        addSlot(new Slot(inventory, index));
    onCraftMatrixChanged(craftMatrix);
}
