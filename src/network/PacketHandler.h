#ifndef __Serveur__PacketHandler__
#define __Serveur__PacketHandler__

#include "Types.h"

class PacketHandshake;
class PacketLoginStart;
class PlayerConnection;

class PacketHandler {
public:
    PacketHandler(PlayerConnection*);

    void handleHandshake(PacketHandshake*);

    void handleLoginStart(PacketLoginStart*);

private:
    PlayerConnection *connect;
    string_t username;
    string_t uuid;
};

#endif /* defined(__Serveur__PacketHandler__) */
