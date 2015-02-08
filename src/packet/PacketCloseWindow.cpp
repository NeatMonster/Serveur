#include "PacketCloseWindow.h"

#include "PacketHandler.h"

void PacketCloseWindow::read(PacketBuffer& buffer) {
    buffer.getByte(windowId);
}

void PacketCloseWindow::handle(PacketHandler *handler) {
    handler->handleCloseWindow(this);
}
