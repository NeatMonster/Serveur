#include "PacketClickWindow.h"

#include "PacketHandler.h"

PacketClickWindow::PacketClickWindow() {}

void PacketClickWindow::read(PacketBuffer &buffer) {
    buffer.getByte(windowId);
    buffer.getShort(slotId);
    buffer.getByte(usedButton);
    buffer.getShort(actionNumber);
    buffer.getByte(mode);
    buffer.getItemStack(clickedItem);
}

void PacketClickWindow::handle(PacketHandler *handler) {
    handler->handleClickWindow(this);
}
