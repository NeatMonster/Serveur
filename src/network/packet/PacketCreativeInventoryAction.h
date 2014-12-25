#ifndef __Serveur__PacketCreativeInventoryAction__
#define __Serveur__PacketCreativeInventoryAction__

#include "ClientPacket.h"
#include "SlotData.h"

class PacketCreativeInventoryAction : public ClientPacket
{
public:
    void read(ByteBuffer&);

    void handle(PacketHandler*);

    short_t slot;
    SlotData* clickedItem;

    ~PacketCreativeInventoryAction();
};

#endif
