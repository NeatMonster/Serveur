#ifndef __Serveur__PacketConfirmTransaction__
#define __Serveur__PacketConfirmTransaction__

#include "ClientPacket.h"
#include "ServerPacket.h"

class PacketConfirmTransaction : public ClientPacket, public ServerPacket {
public:
    byte_t windowId;
    short_t actionNumber;
    bool accepted;

    PacketConfirmTransaction();

    void read(PacketBuffer&);

    void write(PacketBuffer&);

    void handle(PacketHandler*);
};

#endif /* defined(__Serveur__PacketConfirmTransaction__) */
