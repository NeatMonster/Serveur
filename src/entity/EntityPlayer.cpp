#include "EntityPlayer.h"

#include "Chunk.h"
#include "Level.h"
#include "PacketChatMessage.h"
#include "PacketChunkData.h"
#include "PacketDestroyEntities.h"
#include "PacketJoinGame.h"
#include "PacketMapChunkBulk.h"
#include "PacketPlayerAbilities.h"
#include "PacketPlayerListItem.h"
#include "PacketPlayerPositionLook.h"
#include "PacketSpawnPlayer.h"
#include "PacketSpawnPosition.h"
#include "PacketTimeUpdate.h"
#include "PlayerConnection.h"
#include "Server.h"
#include "World.h"

EntityPlayer::EntityPlayer(World *world, PlayerConnection *connect) : EntityLiving(world), connect(connect), inventory() {
    uuid = connect->getProfile()->getUUID();
    name = connect->getProfile()->getName();
}

Entity::Type EntityPlayer::getType() {
    return Type::PLAYER;
}

World *EntityPlayer::getWorld() {
    return Entity::getWorld();
}

void EntityPlayer::move(double_t x, double_t y, double_t z) {
    int_t xOld = (int_t) floor(this->posX) >> 4;
    int_t zOld = (int_t) floor(this->posZ) >> 4;
    EntityLiving::move(x, y, z);
    int_t xNew = (int_t) floor(x) >> 4;
    int_t zNew = (int_t) floor(z) >> 4;
    if (xOld == xNew && zOld == zNew)
        return;
    world->getChunk(xOld, zOld)->removePlayer(this);
    world->getChunk(xNew, zNew)->addPlayer(this);
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++)
            if (xNew + x < xOld - VIEW_DISTANCE || xNew + x > xOld + VIEW_DISTANCE
                    || zNew + z < zOld - VIEW_DISTANCE || zNew + z > zOld + VIEW_DISTANCE) {
                Chunk *chunk = world->getChunk(xNew + x, zNew + z);
                sendPacket(new PacketChunkData(chunk, false));
                for (EntityPlayer *const &player : chunk->getPlayers())
                    if (player != this) {
                        sendPacket(new PacketSpawnPlayer(player));
                        player->sendPacket(new PacketSpawnPlayer(this));
                    }
            }
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++)
            if (xOld + x < xNew - VIEW_DISTANCE || xOld + x > xNew + VIEW_DISTANCE
                    || zOld + z < zNew - VIEW_DISTANCE || zOld + z > zNew + VIEW_DISTANCE) {
                Chunk *chunk = world->getChunk(xOld + x, zOld + z);
                sendPacket(new PacketChunkData(chunk, true));
                std::unordered_set<varint_t> entitiesIds;
                for (EntityPlayer *const &player : chunk->getPlayers())
                    if (player != this) {
                        entitiesIds.insert(player->getEntityId());
                        player->sendPacket(new PacketDestroyEntities({(varint_t) getEntityId()}));
                    }
                if (!entitiesIds.empty())
                    sendPacket(new PacketDestroyEntities(entitiesIds));
            }
}

string_t EntityPlayer::getUUID() {
    return uuid;
}

string_t EntityPlayer::getName() {
    return name;
}

PlayerConnection *EntityPlayer::getConnection() {
    return connect;
}

InventoryPlayer &EntityPlayer::getInventory() {
    return inventory;
}

void EntityPlayer::sendMessage(ChatMessage &message) {
    sendPacket(new PacketChatMessage(message.getJSON()));
}

void EntityPlayer::disconnect(string_t reason) {
    if (connect != nullptr)
        connect->disconnect(reason);
}

void EntityPlayer::sendPacket(ServerPacket *packet) {
    if (connect != nullptr)
        connect->sendPacket(packet);
}

void EntityPlayer::onJoinGame() {
    PacketJoinGame *joinPacket = new PacketJoinGame();
    joinPacket->entityId = entityId;
    joinPacket->gamemode = 1;
    joinPacket->dimension = 0;
    joinPacket->difficulty = 0;
    joinPacket->maxPlayers = 20;
    joinPacket->levelType = "default";
    joinPacket->reducedDebugInfo = false;
    sendPacket(joinPacket);

    sendPacket(new PacketSpawnPosition(posX, posY, posZ));

    PacketPlayerAbilities *abilPacket = new PacketPlayerAbilities();
    abilPacket->godMode = true;
    abilPacket->canFly = true;
    abilPacket->isFlying = true;
    abilPacket->creativeMode = true;
    abilPacket->flyingSpeed = 0.05;
    abilPacket->walkingSpeed = 0.1;
    sendPacket(abilPacket);

    Server::broadcast(Chat() << Color::YELLOW << name << " a rejoint la partie");

    std::unordered_set<EntityPlayer*> players = Server::getPlayers();
    for (EntityPlayer *const &player : players)
        player->sendPacket(new PacketPlayerListItem(PacketPlayerListItem::Type::ADD_PLAYER, {this}));
    players.insert(this);
    sendPacket(new PacketPlayerListItem(PacketPlayerListItem::Type::ADD_PLAYER, players));
    Server::getServer()->addPlayer(this);

    PacketPlayerPositionLook *posPacket = new PacketPlayerPositionLook();
    posPacket->x = posX;
    posPacket->y = posY;
    posPacket->z = posZ;
    posPacket->yaw = rotYaw;
    posPacket->pitch = rotPitch;
    posPacket->flags = 0;
    sendPacket(posPacket);

    sendPacket(new PacketTimeUpdate(world->getLevel()->getTime(), world->getLevel()->getDayTime()));
    int_t xChunk = (int_t) floor(posX) >> 4;
    int_t zChunk = (int_t) floor(posZ) >> 4;
    std::vector<Chunk*> chunks = {world->getChunk(xChunk, zChunk)};
    for (int_t distance = 1; distance <= VIEW_DISTANCE; distance++) {
        for (int_t x = -distance; x < distance; x++)
            chunks.push_back(world->getChunk(xChunk + x, zChunk - distance));
        for (int_t z = -distance; z < distance; z++)
            chunks.push_back(world->getChunk(xChunk + distance, zChunk + z));
        for (int_t x = distance; x > -distance; x--)
            chunks.push_back(world->getChunk(xChunk + x, zChunk + distance));
        for (int_t z = distance; z > -distance; z--)
            chunks.push_back(world->getChunk(xChunk - distance, zChunk + z));
    }
    std::vector<Chunk*> packetChunks;
    for (Chunk *&chunk : chunks) {
        if (packetChunks.size() == 10) {
            sendPacket(new PacketMapChunkBulk(packetChunks));
            for (Chunk *&packetChunk : packetChunks)
                for (EntityPlayer *const &player : packetChunk->getPlayers())
                    if (player != this)
                        sendPacket(new PacketSpawnPlayer(player));
            packetChunks.clear();
        }
        packetChunks.push_back(chunk);
    }
    if (!packetChunks.empty()) {
        sendPacket(new PacketMapChunkBulk(packetChunks));
        for (Chunk *&packetChunk : packetChunks)
            for (EntityPlayer *const &player : packetChunk->getPlayers())
                if (player != this)
                    sendPacket(new PacketSpawnPlayer(player));
    }
    packetChunks.clear();
}

void EntityPlayer::onQuitGame() {
    Server::getServer()->removePlayer(this);
    Server::broadcast(Chat() << Color::YELLOW << name << " a quitté la partie");

    for (EntityPlayer *const &player : Server::getPlayers())
        player->sendPacket(new PacketPlayerListItem(PacketPlayerListItem::Type::REMOVE_PLAYER, {this}));
}

ServerPacket *EntityPlayer::getSpawnPacket() {
    return new PacketSpawnPlayer(this);
}

ServerPacket *EntityPlayer::getMetadataPacket() {
    return nullptr;
}
