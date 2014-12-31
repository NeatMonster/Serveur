#ifndef __Serveur__PacketPlayerListItem__
#define __Serveur__PacketPlayerListItem__

#include "ServerPacket.h"

#include <unordered_set>
#include <vector>

class Player;

class PacketPlayerListItem : public ServerPacket {
public:
    enum Type {ADD_PLAYER, UPDATE_GAMEMODE, UPDATE_LATENCY, UPDATE_DISPLAY_NAME, REMOVE_PLAYER};

    PacketPlayerListItem(Type, std::unordered_set<Player*>);

    void write(PacketBuffer&);

private:
    struct Action {
        string_t uuid;
        string_t name;
        varint_t gameMode;
        varint_t ping;
        bool hasDisplayName;
        string_t displayName;
    };

    Type type;
    std::vector<Action> actions;
};

#endif /* defined(__Serveur__PacketPlayerListItem__) */
