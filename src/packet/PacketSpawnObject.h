#ifndef __Serveur__PacketSpawnObject__
#define __Serveur__PacketSpawnObject__

#include "ServerPacket.h"

class Entity;

class PacketSpawnObject : public ServerPacket {
public:
    PacketSpawnObject(Entity*, int_t);

    void write(PacketBuffer&);

private:
    varint_t entityId;
    byte_t type;
    int_t x;
    int_t y;
    int_t z;
    byte_t pitch;
    byte_t yaw;
    int_t data;
    short_t motX;
    short_t motY;
    short_t motZ;
};

#endif /* defined(__Serveur__PacketSpawnObject__) */
