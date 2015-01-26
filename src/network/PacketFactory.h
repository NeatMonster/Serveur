#ifndef __Serveur__PacketFactory__
#define __Serveur__PacketFactory__

#include "ClientPacket.h"

#include <map>

class PacketFactory {
public:
    PacketFactory();

    std::shared_ptr<ClientPacket> createPacket(const varint_t);

    bool hasPacket(const varint_t);

private:
    typedef std::shared_ptr<ClientPacket> (*cons_t)();
    std::map<const varint_t, cons_t> packets;

    template<typename T>
    static std::shared_ptr<ClientPacket> constructPacket();

    template<typename T>
    void registerPacket(const varint_t);
};

#endif /* defined(__Serveur__PacketFactory__) */
