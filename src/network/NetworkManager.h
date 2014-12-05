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

    void handlePackets();

    bool start();

    bool stop();

private:
    bool running;
    std::thread thread;
    ServerSocket *socket;
    std::vector<PlayerConnection*> connects;

    void run();
};

#endif /* defined(__Serveur__NetworkManager__) */
