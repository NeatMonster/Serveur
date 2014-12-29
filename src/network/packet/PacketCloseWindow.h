#ifndef __Serveur__PacketCloseWindow__
#define __Serveur__PacketCloseWindow__

#include "ClientPacket.h"

class PacketCloseWindow : public ClientPacket {
public:
    byte_t windowId;

    void read(PacketBuffer&);
};

#endif /* defined(__Serveur__PacketCloseWindow__) */
