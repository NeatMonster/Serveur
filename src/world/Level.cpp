#include "Level.h"

#include "Compression.h"
#include "NBTTag.h"
#include "NBTTagByte.h"
#include "NBTTagCompound.h"
#include "NBTTagLong.h"
#include "NBTTagInt.h"

Level::Level(string_t worldName) {
    file.open(worldName + "/level.dat", std::fstream::in | std::fstream::out | std::ios::binary);
    file.seekg(0, file.end);
    int_t length = file.tellg();
    file.seekg(0, file.beg);
    if (length > 0) {
        ubytes_t bytes(length);
        file.read((char*) bytes.data(), length);
        ubyte_t *plain = Compression::inflateGzip(bytes.data(), length).first;
        ubyte_t *copy = (ubyte_t*)(plain);
        std::shared_ptr<NBTTagCompound> data = NBTTag::read(copy)->asCompound()->get("Data")->asCompound();
        time = data->get("Time")->asLong()->get();
        dayTime = data->get("DayTime")->asLong()->get();
        difficulty = Difficulty(data->get("Difficulty")->asByte()->get());
        int_t spawnX = data->get("SpawnX")->asInt()->get();
        int_t spawnY = data->get("SpawnY")->asInt()->get();
        int_t spawnZ = data->get("SpawnZ")->asInt()->get();
        spawn = Position(spawnX, spawnY, spawnZ);
        std::free(plain);
    } else {
        time = dayTime = 0;
        spawn = Position(8, 4, 8);
    }
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

Position Level::getSpawn() {
    return spawn;
}

void Level::setSpawn(Position spawn) {
    this->spawn = spawn;
}

Level::Difficulty Level::getDifficulty() {
    return difficulty;
}

void Level::setDifficulty(Difficulty diff) {
    this->difficulty = diff;
}

GameRules& Level::getGameRules() {
    return gamerules;
}
