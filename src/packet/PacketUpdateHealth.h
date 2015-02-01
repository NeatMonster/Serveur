#ifndef __Serveur__PacketUpdateHealth__
#define __Serveur__PacketUpdateHealth__

#include "ServerPacket.h"

class PacketUpdateHealth : public ServerPacket {
public:
    float_t health;
    varint_t foodLevel;
    float_t foodSaturationLevel;

    PacketUpdateHealth();

    void write(PacketBuffer&);
};

#endif // __Serveur__PacketUpdateHealth__
