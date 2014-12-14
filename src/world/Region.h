#ifndef __Serveur__Region__
#define __Serveur__Region__

#include "Chunk.h"
#include "Types.h"
#include "World.h"

#include <fstream>

class Region {
public:
    Region(string_t, int_t, int_t);

    ~Region();

    bool getChunk(Chunk*);

private:
    std::fstream file;
    int_t locations[1024];
    int_t timestamps[1024];

    static void reverse(int_t*);
};

#endif /* defined(__Serveur__Region__) */
