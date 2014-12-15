#include "PacketPlayerListItem.h"

#include "Player.h"

#include <iomanip>

PacketPlayerListItem::PacketPlayerListItem(Type type, std::unordered_set<Player*> players) : ServerPacket(0x38) {
    this->type = type;
    for (Player *const &player : players) {
        Action action;
        action.uuid = player->getUUID();
        action.name = player->getName();
        action.gameMode = 1;
        action.ping = player->getPing();
        action.hasDisplayName = false;
        actions.push_back(action);
    }
}

void PacketPlayerListItem::write(ByteBuffer &buffer) {
    buffer.putVarInt(type);
    buffer.putVarInt(actions.size());
    for (Action const &action : actions) {
        buffer.putLong(std::stoull(action.uuid.substr(0, 8)
                                 + action.uuid.substr(9, 4)
                                 + action.uuid.substr(14, 4), nullptr, 16));
        buffer.putLong(std::stoull(action.uuid.substr(19, 4)
                                 + action.uuid.substr(24, 12), nullptr, 16));
        if (type ==  Type::ADD_PLAYER) {
                buffer.putString(action.name);
                buffer.putVarInt(0);
        }
        if (type == Type::ADD_PLAYER || type == Type::UPDATE_GAMEMODE)
            buffer.putVarInt(action.gameMode);
        if (type == Type::ADD_PLAYER || type == Type::UPDATE_LATENCY)
            buffer.putVarInt(action.ping);
        if (type == Type::ADD_PLAYER || type == Type::UPDATE_DISPLAY_NAME) {
            buffer.putBool(action.hasDisplayName);
            if (action.hasDisplayName)
                buffer.putString(action.displayName);
        }
    }
}
