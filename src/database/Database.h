#ifndef __Serveur__Database__
#define __Serveur__Database__

#include "mongo/client/dbclient.h"

class Database {
public:
    Database();

    bool run();

private:
    mongo::DBClientConnection c;
};

#endif /* defined(__Serveur__Database__) */
