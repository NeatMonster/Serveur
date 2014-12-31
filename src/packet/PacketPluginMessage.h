#ifndef __Serveur__PacketPluginMessage__
#define __Serveur__PacketPluginMessage__

#include "ClientPacket.h"

class PacketPluginMessage : public ClientPacket {
public:
    string_t channel;
    ubytes_t data;

    void read(PacketBuffer&);
};

#endif /* defined(__Serveur__PacketPluginMessage__) */
