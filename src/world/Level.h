#ifndef __Serveur__Level__
#define __Serveur__Level__

#include "Types.h"

#include <fstream>

class Level {
public:
    Level(string_t);

    ~Level();

    long_t getTime();

    void setTime(long_t);

    int_t getDayTime();

    void setDayTime(int_t);

    Position getSpawn();

    void setSpawn(Position);

private:
    std::fstream file;
    long_t time;
    int_t dayTime;
    Position spawn;
};

#endif /* defined(__Serveur__Level__) */
