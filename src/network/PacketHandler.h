#ifndef __Serveur__PacketHandler__
#define __Serveur__PacketHandler__

#include "Types.h"

class PacketChatMessage;
class PacketHandshake;
class PacketKeepAlive;
class PacketLoginStart;
class PacketPlayer;
class PacketPlayerLook;
class PacketPlayerPosition;
class PacketPlayerPositionLook;
class PlayerConnection;

class PacketHandler {
    friend class PlayerConnection;

public:
    PacketHandler(PlayerConnection*);

    void handleHandshake(PacketHandshake*);

    void handleLoginStart(PacketLoginStart*);

    void handleKeepAlive(PacketKeepAlive*);

    void handleChatMessage(PacketChatMessage*);

    void handlePlayer(PacketPlayer*);

    void handlePlayerLook(PacketPlayerLook*);

    void handlePlayerPosition(PacketPlayerPosition*);

    void handlePlayerPositionLook(PacketPlayerPositionLook*);

private:
    PlayerConnection *connect;
    string_t name;
    string_t uuid;
};

#endif /* defined(__Serveur__PacketHandler__) */
