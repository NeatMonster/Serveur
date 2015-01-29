#ifndef __Serveur__PacketSetSlot__
#define __Serveur__PacketSetSlot__

#include "ServerPacket.h"

class PacketSetSlot : public ServerPacket {
public:
    byte_t windowId;
    short_t slot;
    std::shared_ptr<ItemStack> stack;

    PacketSetSlot();

    void write(PacketBuffer&);
};

#endif /* defined(__Serveur__PacketSetSlot__) */
