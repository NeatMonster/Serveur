#include "Player.h"

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

Player::Player(World *world, PlayerConnection *connect) : LivingEntity(world), connect(connect) {
    uuid = connect->getUUID();
    name = connect->getName();
    world->addPlayer(this);
    onJoinGame();
    Server::getServer()->addPlayer(this);
}

Player::~Player() {
    Server::getServer()->removePlayer(this);
    world->removePlayer(this);
    onQuitGame();
}

Entity::Type Player::getType() {
    return Type::PLAYER;
}

void Player::move(double_t x, double_t y, double_t z) {
    int_t xOld = (int_t) floor(this->x) >> 4;
    int_t zOld = (int_t) floor(this->z) >> 4;
    LivingEntity::move(x, y, z);
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
                for (Player *const &player : chunk->getPlayers())
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
                for (Player *const &player : chunk->getPlayers())
                    if (player != this) {
                        entitiesIds.insert(player->getEntityId());
                        player->sendPacket(new PacketDestroyEntities({(varint_t) getEntityId()}));
                    }
                if (!entitiesIds.empty())
                    sendPacket(new PacketDestroyEntities(entitiesIds));
            }
}

string_t Player::getUUID() {
    return uuid;
}

string_t Player::getName() {
    return name;
}

string_t Player::getIP() {
    return connect->getIP();
}

ushort Player::getPort() {
    return connect->getPort();
}

float_t Player::getPing() {
    return connect->getPing();
}

void Player::sendMessage(ChatMessage &message) {
    sendPacket(new PacketChatMessage(message.getJSON()));
}

void Player::disconnect(string_t reason) {
    connect->disconnect(reason);
}

void Player::sendPacket(ServerPacket *packet) {
    connect->sendPacket(packet);
}

void Player::onJoinGame() {
    PacketJoinGame *joinPacket = new PacketJoinGame();
    joinPacket->entityId = entityId;
    joinPacket->gameMode = 1;
    joinPacket->dimension = 0;
    joinPacket->difficulty = 0;
    joinPacket->maxPlayers = 20;
    joinPacket->levelType = "default";
    joinPacket->reducedDebugInfo = false;
    sendPacket(joinPacket);

    sendPacket(new PacketSpawnPosition(x, y, z));

    PacketPlayerAbilities *abilPacket = new PacketPlayerAbilities();
    abilPacket->godMode = true;
    abilPacket->canFly = true;
    abilPacket->isFlying = true;
    abilPacket->creativeMode = true;
    abilPacket->flyingSpeed = 0.05;
    abilPacket->walkingSpeed = 0.1;
    sendPacket(abilPacket);

    std::unordered_set<Player*> players = Server::getPlayers();
    for (Player *const &player : players)
        player->sendPacket(new PacketPlayerListItem(PacketPlayerListItem::Type::ADD_PLAYER, {this}));
    players.insert(this);
    sendPacket(new PacketPlayerListItem(PacketPlayerListItem::Type::ADD_PLAYER, players));

    PacketPlayerPositionLook *posPacket = new PacketPlayerPositionLook();
    posPacket->x = x;
    posPacket->y = y;
    posPacket->z = z;
    posPacket->yaw = yaw;
    posPacket->pitch = pitch;
    posPacket->flags = 0;
    sendPacket(posPacket);

    sendPacket(new PacketTimeUpdate(world->getLevel()->getTime(), world->getLevel()->getDayTime()));
    int_t xChunk = (int_t) floor(x) >> 4;
    int_t zChunk = (int_t) floor(z) >> 4;
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
                for (Player *const &player : packetChunk->getPlayers())
                    if (player != this) {
                        sendPacket(new PacketSpawnPlayer(player));
                        player->sendPacket(new PacketSpawnPlayer(this));
                    }
            packetChunks.clear();
        }
        packetChunks.push_back(chunk);
    }
    if (!packetChunks.empty()) {
        sendPacket(new PacketMapChunkBulk(packetChunks));
        for (Chunk *&packetChunk : packetChunks)
            for (Player *const &player : packetChunk->getPlayers())
                if (player != this) {
                    sendPacket(new PacketSpawnPlayer(player));
                    player->sendPacket(new PacketSpawnPlayer(this));
                }
    }
}
void Player::onQuitGame() {
    for (Player *const &watcher : getWatchers())
        watcher->sendPacket(new PacketDestroyEntities({(varint_t) getEntityId()}));

    for (Player *const &player : Server::getPlayers())
        player->sendPacket(new PacketPlayerListItem(PacketPlayerListItem::Type::REMOVE_PLAYER, {this}));
}

void Player::onTick() {
    LivingEntity::onTick();
}