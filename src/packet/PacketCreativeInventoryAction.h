#ifndef __Serveur__PacketCreativeInventoryAction__
#define __Serveur__PacketCreativeInventoryAction__

#include "ClientPacket.h"
#include "ItemStack.h"

class PacketCreativeInventoryAction : public ClientPacket {
public:
    short_t slot;
    std::shared_ptr<ItemStack> stack;

    void read(PacketBuffer&);

    void handle(PacketHandler*);
};

#endif /* defined(__Serveur__PacketCreativeInventoryAction__) */
