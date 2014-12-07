#include "Player.h"

#include "Chunk.h"
#include "PlayerConnection.h"
#include "World.h"

Player::Player(World *world, PlayerConnection *connect) : LivingEntity(world), connect(connect) {
    uuid = connect->getUUID();
    name = connect->getName();
}

Player::~Player() {}

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
                        || newChunk->getZ() + z > oldChunk->getZ() + VIEW_DISTANCE) {
                //TODO : Envoyer les paquets.
                Chunk *chunk = world->getChunk(std::make_pair(newChunk->getX() + x, newChunk->getZ() + z));
                /*PacketChunkData *packet = new PacketChunkData();
                packet->continuous = true;
                packet->meta = chunk->getMeta();
                packet->size = chunk->getSize(getVersion());
                packet->data = new ubyte_t[packet->size];
                ubyte_t *data = packet->data;
                chunk->writeData(data, getVersion());
                sendPacket(packet);*/
            }
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++)
            if (oldChunk->getX() + x < newChunk->getX() - VIEW_DISTANCE
                || oldChunk->getX() + x > newChunk->getX() + VIEW_DISTANCE
                    || oldChunk->getZ() + z < newChunk->getZ() - VIEW_DISTANCE
                        || oldChunk->getZ() + z > newChunk->getZ() + VIEW_DISTANCE) {
                //TODO : Envoyer les paquets.
                /*PacketChunkData *packet = new PacketChunkData();
                packet->continuous = true;
                packet->meta = {xOld + x, zOld + z, 0};
                packet->size = 0;
                packet->data = nullptr;
                sendPacket(packet);
                world->tryUnloadChunk(std::make_pair(xOld + x, zOld + z));*/
            }
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

void Player::sendMessage(string_t) {
    //TODO : Envoyer le paquet.
}

void Player::disconnect(string_t reason) {
    connect->disconnect(reason);
}

void Player::sendPacket(ServerPacket *packet) {
    connect->sendPacket(packet);
}

void Player::onJoinGame() {}

void Player::onLeftGame() {}

void Player::onJoinWorld() {}

void Player::onLeftWorld() {}

void Player::onTick() {
    LivingEntity::onTick();
}