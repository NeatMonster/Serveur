#include "Level.h"

#include "Compression.h"
#include "NBTTag.h"
#include "NBTTagCompound.h"
#include "NBTTagLong.h"
#include "NBTTagInt.h"

Level::Level(string_t worldName) {
    file = std::fstream(worldName + "/level.dat",
                        std::fstream::in | std::fstream::out | std::ios::binary);
    file.seekg(0, file.end);
    int_t length = file.tellg();
    file.seekg(0, file.beg);
    if (length > 0) {
        ubytes_t bytes(length);
        file.read((char*) bytes.data(), length);
        ubyte_t *plain = Compression::inflateGzip(bytes.data(), length).first;
        ubyte_t *copy = (ubyte_t*)(plain);
        NBTTag *root = NBTTag::read(copy);
        NBTTagCompound *data = root->asCompound()->get("Data")->asCompound();
        time = data->get("Time")->asLong()->get();
        dayTime = data->get("DayTime")->asLong()->get();
        int_t spawnX = data->get("SpawnX")->asInt()->get();
        int_t spawnY = data->get("SpawnY")->asInt()->get() + 20; // Remove me. :)
        int_t spawnZ = data->get("SpawnZ")->asInt()->get();
        spawn = position_t(spawnX, spawnY, spawnZ);
        delete root;
        delete plain;
    } else {
        time = dayTime = 0;
        spawn = position_t(8, 4, 8);
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

position_t Level::getSpawn() {
    return spawn;
}

void Level::setSpawn(position_t spawn) {
    this->spawn = spawn;
}
