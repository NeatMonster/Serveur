#ifndef __Serveur__PacketPluginMessage__
#define __Serveur__PacketPluginMessage__

#include "ClientPacket.h"
#include "ServerPacket.h"

class PacketPluginMessage : public ClientPacket, public ServerPacket {
public:
    string_t channel;
    ubytes_t data;

    PacketPluginMessage();

    void read(PacketBuffer&);

    void write(PacketBuffer&);

    void handle(PacketHandler*);
};

#endif /* defined(__Serveur__PacketPluginMessage__) */
