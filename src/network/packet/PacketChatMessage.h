#ifndef __Serveur__PacketChatMessage__
#define __Serveur__PacketChatMessage__

#include "ClientPacket.h"
#include "PacketHandler.h"
#include "ServerPacket.h"

class PacketChatMessage : public ClientPacket, public ServerPacket {
public:
    string_t message;
    byte_t position;

    PacketChatMessage();

    PacketChatMessage(string_t);

    void read(ByteBuffer&);

    void write(ByteBuffer&);

    void handle(PacketHandler*);
};

#endif /* defined(__Serveur__PacketChatMessage__) */