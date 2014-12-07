#ifndef __Serveur__Player__
#define __Serveur__Player__

#include "ChatMessage.h"
#include "LivingEntity.h"

class PlayerConnection;
class ServerPacket;

class Player : public LivingEntity {
public:
    Player(World*, PlayerConnection*);

    virtual ~Player();

    virtual Type getType();

    void setPosition(double_t, double_t, double_t);

    void setRotation(float_t, float_t);

    string_t getUUID();

    string_t getName();

    string_t getIP();

    ushort_t getPort();

    void sendMessage(ChatMessage&);

    void disconnect(string_t);

    void sendPacket(ServerPacket*);

    void onJoinGame();

    void onQuitGame();

    void onJoinWorld();

    void onQuitWorld();

    virtual void onTick();

private:
    PlayerConnection *connect;
    string_t uuid;
    string_t name;
};

#endif /* defined(__Serveur__Player__) */
