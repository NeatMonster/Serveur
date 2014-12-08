#ifndef __Serveur__NetworkManager__
#define __Serveur__NetworkManager__

#include "PlayerConnection.h"
#include "ServerSocket.h"

#include <thread>
#include <vector>

class NetworkManager {
public:
    NetworkManager();

    ~NetworkManager();

    varint_t getKeepAliveId();

    bool start();

    bool stop();

    void handlePackets();

private:
    bool running;
    std::thread thread;
    ServerSocket *socket;
    std::vector<PlayerConnection*> connects;
    varint_t keepAliveId;
    std::thread keepAliveThread;

    void run();

    void runKeepAlive();
};

#endif /* defined(__Serveur__NetworkManager__) */
