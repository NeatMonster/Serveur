#include "PacketTimeUpdate.h"

PacketTimeUpdate::PacketTimeUpdate(long_t time, long_t dayTime) : ServerPacket(0x03) {
    this->time = time;
    this->dayTime = dayTime;
};

void PacketTimeUpdate::write(ByteBuffer &buffer) {
    buffer.putLong(time);
    buffer.putLong(dayTime);
}
