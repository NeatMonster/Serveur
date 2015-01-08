#ifndef __Serveur__Database__
#define __Serveur__Database__

#include "Profile.h"
#include "Types.h"

#include "mongo/client/dbclient.h"

class Database {
public:
    Database();

    bool run();

    Profile *getProfile(string_t);

private:
    mongo::DBClientConnection c;
};

#endif /* defined(__Serveur__Database__) */
