#ifndef __Serveur__Level__
#define __Serveur__Level__

#include "GameRules.h"
#include "Types.h"

#include <fstream>

class Level {
public:
    enum Difficulty {PEACEFUL = 0, EASY = 1, NORMAL = 2, HARD = 3};

    Level(string_t);

    ~Level();

    long_t getTime();

    void setTime(long_t);

    int_t getDayTime();

    void setDayTime(int_t);

    Position getSpawn();

    void setSpawn(Position);

    Difficulty getDifficulty();

    void setDifficulty(Difficulty);

    GameRules& getGameRules();

private:
    std::fstream file;
    long_t time;
    int_t dayTime;
    Position spawn;
    Difficulty difficulty;
    GameRules gamerules;
};

#endif /* defined(__Serveur__Level__) */
