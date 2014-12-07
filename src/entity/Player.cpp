#include "Player.h"

#include "Chunk.h"
#include "Level.h"
#include "PacketChatMessage.h"
#include "PacketChunkData.h"
#include "PacketJoinGame.h"
#include "PacketPlayerListItem.h"
#include "PlayerConnection.h"
#include "Server.h"
#include "World.h"

Player::Player(World *world, PlayerConnection *connect) : LivingEntity(world), connect(connect) {
    uuid = connect->getUUID();
    name = connect->getName();
    position_t spawn = world->getLevel()->getSpawn();
    onJoinGame();
    Server::getServer()->addPlayer(this);
    setPosition(spawn.x, spawn.y, spawn.z);
    world->addPlayer(this);
}

Player::~Player() {
    world->removePlayer(this);
    Server::getServer()->removePlayer(this);
    onQuitGame();
}

Entity::Type Player::getType() {
    return Type::PLAYER;
}

void Player::setPosition(double_t x, double_t y, double_t z) {
    Chunk *oldChunk = getChunk();
    LivingEntity::setPosition(x, y, z);
    Chunk *newChunk = getChunk();
    if (oldChunk == newChunk)
        return;
    oldChunk->removePlayer(this);
    newChunk->addPlayer(this);
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int_t z = - VIEW_DISTANCE; z <= VIEW_DISTANCE; z++)
            if (newChunk->getX() + x < oldChunk->getX() - VIEW_DISTANCE
                || newChunk->getX() + x > oldChunk->getX() + VIEW_DISTANCE
                    || newChunk->getZ() + z < oldChunk->getZ() - VIEW_DISTANCE
                        || newChunk->getZ() + z > oldChunk->getZ() + VIEW_DISTANCE)
                sendPacket(new PacketChunkData(world->getChunk(std::make_pair(newChunk->getX() + x,
                                                                              newChunk->getZ() + z)), false));
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++)
            if (oldChunk->getX() + x < newChunk->getX() - VIEW_DISTANCE
                || oldChunk->getX() + x > newChunk->getX() + VIEW_DISTANCE
                    || oldChunk->getZ() + z < newChunk->getZ() - VIEW_DISTANCE
                        || oldChunk->getZ() + z > newChunk->getZ() + VIEW_DISTANCE)
                sendPacket(new PacketChunkData(world->getChunk(std::make_pair(newChunk->getX() + x,
                                                                              newChunk->getZ() + z)), true));
}

void Player::setRotation(float_t yaw, float_t pitch) {
    if (abs<float_t>(this->yaw - yaw) > 15.)
        LivingEntity::setRotation(this->yaw + yaw - headYaw, pitch);
    else
        LivingEntity::setRotation(this->yaw, pitch);
    LivingEntity::setHeadRotation(yaw);
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

    sendPacket(new PacketPlayerListItem(PacketPlayerListItem::Type::ADD_PLAYER, Server::getPlayers()));
    for (Player *player : Server::getPlayers())
        player->sendPacket(new PacketPlayerListItem(PacketPlayerListItem::Type::ADD_PLAYER, {this}));
}

void Player::onQuitGame() {}

void Player::onJoinWorld() {}

void Player::onQuitWorld() {}

void Player::onTick() {
    LivingEntity::onTick();
}