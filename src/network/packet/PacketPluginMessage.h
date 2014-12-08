#ifndef __Serveur__PacketPluginMessage__
#define __Serveur__PacketPluginMessage__

#include "ClientPacket.h"

class PacketPluginMessage : public ClientPacket {
public:
    string_t channel;
    ubytes_t data;

    PacketPluginMessage();

    void read(ByteBuffer&);
};

#endif /* defined(__Serveur__PacketPluginMessage__) */
