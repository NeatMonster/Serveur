#ifndef __Serveur__PacketSpawnPlayer__
#define __Serveur__PacketSpawnPlayer__

#include "ServerPacket.h"

class EntityPlayer;

class PacketSpawnPlayer : public ServerPacket {
public:
    PacketSpawnPlayer(std::shared_ptr<EntityPlayer>);

    void write(PacketBuffer&);

private:
    varint_t entityId;
    string_t uuid;
    int_t x;
    int_t y;
    int_t z;
    byte_t yaw;
    byte_t pitch;
    short_t currentItem;
    ubytes_t metadata;
};

#endif /* defined(__Serveur__PacketSpawnPlayer__) */
