#include "InventoryPlayer.h"

InventoryPlayer::InventoryPlayer() {
    for (int i = 0; i < 45; i++)
        addSlot(new Slot());
}
