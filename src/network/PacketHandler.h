#ifndef __Serveur__PacketHandler__
#define __Serveur__PacketHandler__

#include "Profile.h"
#include "Types.h"

class PacketAnimation;
class PacketChatMessage;
class PacketHandshake;
class PacketKeepAlive;
class PacketLoginStart;
class PacketPlayer;
class PacketPlayerLook;
class PacketPlayerPosition;
class PacketPlayerPositionLook;
class PacketPluginMessage;
class PacketCreativeInventoryAction;
class PlayerConnection;

class PacketHandler {
    friend class PlayerConnection;

public:
    PacketHandler(PlayerConnection*);

    void handleHandshake(PacketHandshake*);

    void handleLoginStart(PacketLoginStart*);

    void handleKeepAlive(PacketKeepAlive*);

    void handleChatMessage(PacketChatMessage*);

    void handlePluginMessage(PacketPluginMessage*);

    void handlePlayer(PacketPlayer*);

    void handlePlayerLook(PacketPlayerLook*);

    void handlePlayerPosition(PacketPlayerPosition*);

    void handlePlayerPositionLook(PacketPlayerPositionLook*);

    void handleAnimation(PacketAnimation*);

    void handleCreativeInventoryAction(PacketCreativeInventoryAction*);

private:
    PlayerConnection *connect;
    Profile *profile;
};

#endif /* defined(__Serveur__PacketHandler__) */
