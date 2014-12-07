#include "Level.h"

Level::Level(string_t) {
    time = dayTime = 0;
    spawn = position_t(8, 4, 8);
}

Level::~Level() {}

long_t Level::getTime() {
    return time;
}

void Level::setTime(long_t time) {
    this->time = time;
}

int_t Level::getDayTime() {
    return dayTime;
}

void Level::setDayTime(int_t dayTime) {
    this->dayTime = dayTime;
}

position_t Level::getSpawn() {
    return spawn;
}

void Level::setSpawn(position_t spawn) {
    this->spawn = spawn;
}
