#include "PacketConfirmTransaction.h"

#include "Packethandler.h"

PacketConfirmTransaction::PacketConfirmTransaction() : ServerPacket(0x32) {}

void PacketConfirmTransaction::read(PacketBuffer &buffer) {
    buffer.getByte(windowId);
    buffer.getShort(actionNumber);
    buffer.getBool(accepted);
}

void PacketConfirmTransaction::write(PacketBuffer &buffer) {
    buffer.putByte(windowId);
    buffer.putShort(actionNumber);
    buffer.putBool(accepted);
}

void PacketConfirmTransaction::handle(PacketHandler *handler) {
    handler->handleConfirmTransaction(this);
}
