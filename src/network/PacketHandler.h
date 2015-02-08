#ifndef __Serveur__PacketHandler__
#define __Serveur__PacketHandler__

#include "Types.h"

#include <map>

class PacketAnimation;
class PacketChatMessage;
class PacketClickWindow;
class PacketCloseWindow;
class PacketConfirmTransaction;
class PacketCreativeInventoryAction;
class PacketHandshake;
class PacketHeldItemChange;
class PacketKeepAlive;
class PacketLoginStart;
class PacketPlayer;
class PacketPlayerLook;
class PacketPlayerPosition;
class PacketPlayerPositionLook;
class PacketPluginMessage;
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

    void handleClickWindow(PacketClickWindow*);

    void handleConfirmTransaction(PacketConfirmTransaction*);

    void handleCloseWindow(PacketCloseWindow*);

    void handleHeldItemChange(PacketHeldItemChange*);

    void handlePosition(double_t, double_t, double_t, bool);

    void handleRotation(float_t, float_t);

    void update();

private:
    PlayerConnection *connect;
    int dropThreshold;
    std::map<byte_t, short_t> fails;
};

#endif /* defined(__Serveur__PacketHandler__) */
