#ifndef __Serveur__Player__
#define __Serveur__Player__

#include "LivingEntity.h"

class PlayerConnection;
class ServerPacket;

class Player : public LivingEntity {
public:
    Player(World*, PlayerConnection*);

    virtual ~Player();

    string_t getUUID();

    string_t getName();

    void sendMessage(string_t);

    void disconnect(string_t);

    string_t getIP();

    ushort_t getPort();

    void sendPacket(ServerPacket*);

    virtual void onTick();

private:
    PlayerConnection *connect;
    string_t uuid;
    string_t name;
};

#endif /* defined(__Serveur__Player__) */
