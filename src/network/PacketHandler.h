#ifndef __Serveur__PacketHandler__
#define __Serveur__PacketHandler__

#include "Types.h"

class PlayerConnection;

class PacketHandler {
public:
    PacketHandler(PlayerConnection*);

private:
    PlayerConnection *connect;
};

#endif /* defined(__Serveur__PacketHandler__) */
