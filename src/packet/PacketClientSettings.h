#ifndef __Serveur__PacketClientSettings__
#define __Serveur__PacketClientSettings__

#include "ClientPacket.h"

class PacketClientSettings : public ClientPacket {
public:
    string_t locale;
    byte_t viewDistance;
    byte_t chatFlags;
    bool chatColours;
    ubyte_t displayedSkinParts;

    void read(PacketBuffer&);
};

#endif /* defined(__Serveur__PacketClientSettings__) */
