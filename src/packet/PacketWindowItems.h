#ifndef __Serveur__PacketWindowItems__
#define __Serveur__PacketWindowItems__

#include "ServerPacket.h"

class PacketWindowItems : public ServerPacket {
public:
    ubyte_t windowId;
    std::vector<std::shared_ptr<ItemStack>> stacks;

    PacketWindowItems();

    void write(PacketBuffer&);
};

#endif /* defined(__Serveur__PacketWindowItems__) */
