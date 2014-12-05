#ifndef __Serveur__Server__
#define __Serveur__Server__

#include "NetworkManager.h"

class Server {
public:
    static Server *getServer();

    static NetworkManager *getNetwork();

    Server();

    ~Server();

    void stop();

private:
    static Server *instance;
    NetworkManager *network;
    bool running;
    long_t ticks;

    void run();
};

#endif /* defined(__Serveur__Server__) */
