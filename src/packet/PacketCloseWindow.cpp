#include "PacketCloseWindow.h"

void PacketCloseWindow::read(PacketBuffer& buffer) {
    buffer.getByte(windowId);
}
