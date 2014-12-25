#include "PacketCreativeInventoryAction.h"

#include "PacketHandler.h"

PacketCreativeInventoryAction::~PacketCreativeInventoryAction() {
    delete item;
}

void PacketCreativeInventoryAction::read(PacketBuffer &buffer) {
    buffer.getShort(slot);
    buffer.getItemStack(item);
}

void PacketCreativeInventoryAction::handle(PacketHandler *handler) {
    handler->handleCreativeInventoryAction(this);
}
