#ifndef __Serveur__World__
#define __Serveur__World__

#include "Types.h"

class World {
public:
    World(string_t);

    ~World();

    string_t getName();

private:
    string_t name;
};

#endif /* defined(__Serveur__World__) */
