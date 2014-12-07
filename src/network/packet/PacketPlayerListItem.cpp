#include "PacketPlayerListItem.h"

#include "Player.h"

PacketPlayerListItem::PacketPlayerListItem(Type type, std::set<Player*> players) : ServerPacket(0x38) {
    this->type = type;
    for (Player *player : players) {
        Action action;
        action.uuid = player->getUUID();
        action.name = player->getName();
        action.gameMode = 1;
        action.ping = 0;
        action.hasDisplayName = false;
        actions.push_back(action);
    }
}

void PacketPlayerListItem::write(ByteBuffer &buffer) {
    buffer.putVarInt(type);
    buffer.putVarInt(actions.size());
    for (Action &action : actions) {
        UUID uuid(action.uuid);
        buffer.putLong(uuid.msb);
        buffer.putLong(uuid.lsb);
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
