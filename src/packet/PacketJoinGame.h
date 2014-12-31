#ifndef __Serveur__PacketJoinGame__
#define __Serveur__PacketJoinGame__

#include "ServerPacket.h"

class PacketJoinGame : public ServerPacket {
public:
    int_t entityId;
    ubyte_t gameMode;
    byte_t dimension;
    ubyte_t difficulty;
    ubyte_t maxPlayers;
    string_t levelType;
    bool reducedDebugInfo;

    PacketJoinGame();

    void write(PacketBuffer&);
};

#endif /* defined(__Serveur__PacketJoinGame__) */
