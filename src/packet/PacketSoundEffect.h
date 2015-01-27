#ifndef __Serveur__PacketSoundEffect__
#define __Serveur__PacketSoundEffect__

#include "ServerPacket.h"

class PacketSoundEffect : public ServerPacket {
public:
    string_t soundName;
    int_t positionX;
    int_t positionY;
    int_t positionZ;
    float_t volume;
    ubyte_t pitch;

    PacketSoundEffect();

    void write(PacketBuffer&);
};

#endif /* defined(__Serveur__PacketSoundEffect__) */
