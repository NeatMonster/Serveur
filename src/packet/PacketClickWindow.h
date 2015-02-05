#ifndef __Serveur__PacketClickWindow__
#define __Serveur__PacketClickWindow__

#include "ClientPacket.h"
#include "ItemStack.h"

class PacketClickWindow : public ClientPacket {
public:
    byte_t windowId;
    short_t slotId;
    byte_t usedButton;
    short_t actionNumber;
    byte_t mode;
    std::shared_ptr<ItemStack> clickedItem;

    PacketClickWindow();

    void read(PacketBuffer&);

    void handle(PacketHandler*);
};

#endif /* defined(__Serveur__PacketClickWindow__) */
