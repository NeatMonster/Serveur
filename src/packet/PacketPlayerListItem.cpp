#include "PacketPlayerListItem.h"

#include "EntityPlayer.h"
#include "PlayerConnection.h"
#include "Profile.h"

#include <iomanip>

PacketPlayerListItem::PacketPlayerListItem(Type type, std::unordered_set<EntityPlayer*> players) : ServerPacket(0x38) {
    this->type = type;
    for (EntityPlayer *const &player : players) {
        Action action;
        action.uuid = player->getUUID();
        if (type == Type::ADD_PLAYER)
            action.profile = player->getConnection()->getProfile();
        if (type == Type::ADD_PLAYER || type == Type::UPDATE_GAMEMODE)
            action.gameMode = player->getGameMode();
        if (type == Type::ADD_PLAYER || type == Type::UPDATE_LATENCY)
            action.ping = player->getConnection()->getPing();
        if (type == Type::ADD_PLAYER || type == Type::UPDATE_DISPLAY_NAME) {
            action.hasDisplayName = false;
            action.displayName = player->getName();
        }
        actions.push_back(action);
    }
}

void PacketPlayerListItem::write(PacketBuffer &buffer) {
    buffer.putVarInt(type);
    buffer.putVarInt(actions.size());
    for (Action const &action : actions) {
        string_t uuid = action.uuid;
        buffer.putLong(std::stoull(uuid.substr(0, 8) + uuid.substr(9, 4) + uuid.substr(14, 4), nullptr, 16));
        buffer.putLong(std::stoull(uuid.substr(19, 4) + uuid.substr(24, 12), nullptr, 16));
        if (type ==  Type::ADD_PLAYER) {
            buffer.putString(action.profile->getName());
            std::vector<Profile::Property> properties = action.profile->getProperties();
            buffer.putVarInt(properties.size());
            for (Profile::Property &property : properties) {
                buffer.putString(property.name);
                buffer.putString(property.value);
                buffer.putBool(property.isSigned);
                if (property.isSigned)
                    buffer.putString(property.signature);
            }
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
