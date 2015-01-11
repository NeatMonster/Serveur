#ifndef __Serveur__PlayerConnection__
#define __Serveur__PlayerConnection__

#include "ClientSocket.h"
#include "PacketBuffer.h"
#include "PacketFactory.h"
#include "PacketQueue.h"
#include "Profile.h"

#include <atomic>
#include <chrono>
#include <thread>

class ClientPacket;
class EntityPlayer;
class PacketHandler;
class ServerPacket;

class PlayerConnection {
    friend class PacketHandler;

public:
    enum Phase {
        HANDSHAKE, STATUS, LOGIN, PLAY
    };

    typedef std::chrono::high_resolution_clock Clock;

    PlayerConnection(ClientSocket*);

    ~PlayerConnection();

    void join();

    void close();

    bool isClosed();

    Profile *getProfile();

    string_t getIP();

    ushort_t getPort();

    float_t getPing();

    void handlePackets();

    void sendPacket(ServerPacket*);

    void disconnect(string_t);

private:
    static PacketFactory factory;
    ClientSocket *socket;
    std::thread readThread;
    std::thread writeThread;
    PacketBuffer readBuffer;
    PacketBuffer writeBuffer;
    PacketQueue<ClientPacket*> readQueue;
    PacketQueue<ServerPacket*> writeQueue;
    PacketHandler *handler;
    std::atomic<bool> closed;
    std::atomic<Phase> phase;
    EntityPlayer *player;
    Profile *profile;
    Clock::time_point sentKeepAlive;
    Clock::time_point rcvdKeepAlive;
    float_t ping;

    string_t getName();

    void runRead();

    void runWrite();
};

#endif /* defined(__Serveur__PlayerConnection__) */
