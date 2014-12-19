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
    long_t ticks;
    random_t random;
    std::thread thread;
    ServerSocket *socket;
    std::vector<PlayerConnection*> connects;
    varint_t keepAliveId;

    void run();
};

#endif /* defined(__Serveur__NetworkManager__) */
