#ifndef __Serveur__PlayerConnection__
#define __Serveur__PlayerConnection__

#include "ByteBuffer.h"
#include "ClientSocket.h"
#include "PacketFactory.h"
#include "PacketQueue.h"

#include <atomic>
#include <thread>

class ClientPacket;
class PacketHandler;
class Player;
class ServerPacket;

class PlayerConnection {
    friend class PacketHandler;

public:
    enum Phase {
        HANDSHAKE, STATUS, LOGIN, PLAY
    };

    PlayerConnection(ClientSocket*);

    ~PlayerConnection();

    void join();

    void close();

    bool isClosed();

    string_t getName();

    string_t getUUID();

    string_t getIP();

    ushort_t getPort();

    void handlePackets();

    void sendPacket(ServerPacket*);

    void disconnect(string_t);

private:
    static PacketFactory factory;
    ClientSocket *socket;
    std::thread readThread;
    std::thread writeThread;
    ByteBuffer readBuffer;
    ByteBuffer writeBuffer;
    PacketQueue<ClientPacket*> readQueue;
    PacketQueue<ServerPacket*> writeQueue;
    PacketHandler *handler;
    std::atomic<bool> closed;
    std::atomic<Phase> phase;
    Player *player;

    void runRead();

    void runWrite();
};

#endif /* defined(__Serveur__PlayerConnection__) */
