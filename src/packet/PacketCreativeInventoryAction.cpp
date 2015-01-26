#include "PacketCreativeInventoryAction.h"

#include "PacketHandler.h"

void PacketCreativeInventoryAction::read(PacketBuffer &buffer) {
    buffer.getShort(slot);
    buffer.getItemStack(stack);
}

void PacketCreativeInventoryAction::handle(PacketHandler *handler) {
    handler->handleCreativeInventoryAction(this);
}
