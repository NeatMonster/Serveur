#ifndef __Serveur__Level__
#define __Serveur__Level__

#include "Types.h"

#include <fstream>

class Level {
public:
    Level(string_t);

    long_t getTime();

    void setTime(long_t);

    int_t getDayTime();

    void setDayTime(int_t);

    position_t getSpawn();

    void setSpawn(position_t);

private:
    std::fstream file;
    long_t time;
    int_t dayTime;
    position_t spawn;
};

#endif /* defined(__Serveur__Level__) */
