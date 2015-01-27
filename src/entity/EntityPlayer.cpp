#include "EntityPlayer.h"

#include "Chunk.h"
#include "EntityItem.h"
#include "Level.h"
#include "MathUtils.h"
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

#include <cmath>

EntityPlayer::EntityPlayer(World *world, PlayerConnection *connect) : EntityLiving(world), connect(connect),
        gameMode(CREATIVE) {
    uuid = connect->getProfile()->getUUID();
    name = connect->getProfile()->getName();
    setSize(0.6, 1.8);
}

World *EntityPlayer::getWorld() {
    return Entity::getWorld();
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

EntityPlayer::GameMode EntityPlayer::getGameMode() {
    return gameMode;
}

void EntityPlayer::setGameMode(EntityPlayer::GameMode gameMode) {
    this->gameMode = gameMode;
}

void EntityPlayer::sendMessage(ChatMessage &message) {
    sendPacket(std::make_shared<PacketChatMessage>(message.getJSON()));
}

void EntityPlayer::drop(std::shared_ptr<ItemStack> stack) {
    std::shared_ptr<EntityItem> entity = std::make_shared<EntityItem>(world, stack);
    entity->getItem();
    entity->setPosition(posX, posY + 1.32, posZ);
    double_t motX = -sin(rotYaw / 180. * M_PI) * cos(rotPitch / 180. * M_PI) * 0.3;
    double_t motY = -sin(rotPitch / 180. * M_PI) * cos(rotPitch / 180. * M_PI) * 0.3 + 0.1;
    double_t motZ = cos(rotYaw / 180. * M_PI) * cos(rotPitch / 180. * M_PI) * 0.3;
    double_t angle = MathUtils::random_f() * 2. * M_PI;
    double_t length = MathUtils::random_f() * 0.02;
    motX += cos(angle) * length;
    motY += (MathUtils::random_f() - MathUtils::random_f()) * 0.1;
    motZ += sin(angle) * length;
    entity->setVelocity(motX, motY, motZ);
    world->addEntity(entity);
}

void EntityPlayer::disconnect(string_t reason) {
    if (connect != nullptr)
        connect->disconnect(reason);
}

void EntityPlayer::sendPacket(std::shared_ptr<ServerPacket> packet) {
    if (connect != nullptr)
        connect->sendPacket(packet);
}

void EntityPlayer::onJoinGame() {
    std::shared_ptr<PacketJoinGame> joinPacket = std::make_shared<PacketJoinGame>();
    joinPacket->entityId = entityId;
    joinPacket->gameMode = gameMode;
    joinPacket->dimension = 0;
    joinPacket->difficulty = 0;
    joinPacket->maxPlayers = 20;
    joinPacket->levelType = "default";
    joinPacket->reducedDebugInfo = false;
    sendPacket(joinPacket);

    sendPacket(std::make_shared<PacketSpawnPosition>(posX, posY, posZ));

    std::shared_ptr<PacketPlayerAbilities> abilPacket = std::make_shared<PacketPlayerAbilities>();
    abilPacket->godMode = true;
    abilPacket->canFly = true;
    abilPacket->isFlying = true;
    abilPacket->creativeMode = true;
    abilPacket->flyingSpeed = 0.05;
    abilPacket->walkingSpeed = 0.1;
    sendPacket(abilPacket);

    Server::broadcast(Chat() << Color::YELLOW << name << " a rejoint la partie");

    std::unordered_set<EntityPlayer*> players = Server::getPlayers();
    std::shared_ptr<PacketPlayerListItem> listPacket =
        std::make_shared<PacketPlayerListItem>(PacketPlayerListItem::Type::ADD_PLAYER, this);
    for (EntityPlayer *const &player : players)
        player->sendPacket(listPacket);
    players.insert(this);
    sendPacket(std::make_shared<PacketPlayerListItem>(PacketPlayerListItem::Type::ADD_PLAYER, players));
    Server::getServer()->addPlayer(this);

    std::shared_ptr<PacketPlayerPositionLook> posPacket = std::make_shared<PacketPlayerPositionLook>();
    posPacket->x = posX;
    posPacket->y = posY;
    posPacket->z = posZ;
    posPacket->yaw = rotYaw;
    posPacket->pitch = rotPitch;
    posPacket->flags = 0;
    sendPacket(posPacket);

    sendPacket(std::make_shared<PacketTimeUpdate>(world->getLevel()->getTime(), world->getLevel()->getDayTime()));
    int_t xChunk = (int_t) floor(posX) >> 4;
    int_t zChunk = (int_t) floor(posZ) >> 4;
    std::vector<std::shared_ptr<Chunk>> chunks = {world->getChunk(xChunk, zChunk)};
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
    std::vector<std::shared_ptr<Chunk>> packetChunks;
    for (std::shared_ptr<Chunk> chunk : chunks) {
        if (packetChunks.size() == 10) {
            sendPacket(std::make_shared<PacketMapChunkBulk>(packetChunks));
            for (std::shared_ptr<Chunk> packetChunk : packetChunks)
                for (std::shared_ptr<EntityPlayer> player : packetChunk->getPlayers())
                    if (player.get() != this)
                        sendPacket(std::make_shared<PacketSpawnPlayer>(player));
            packetChunks.clear();
        }
        packetChunks.push_back(chunk);
    }
    if (!packetChunks.empty()) {
        sendPacket(std::make_shared<PacketMapChunkBulk>(packetChunks));
        for (std::shared_ptr<Chunk> packetChunk : packetChunks)
            for (std::shared_ptr<EntityPlayer> player : packetChunk->getPlayers())
                if (player.get() != this)
                    sendPacket(std::make_shared<PacketSpawnPlayer>(player));
    }
    packetChunks.clear();
}

void EntityPlayer::onQuitGame() {
    Server::getServer()->removePlayer(this);
    Server::broadcast(Chat() << Color::YELLOW << name << " a quitté la partie");

    std::shared_ptr<PacketPlayerListItem> packet =
        std::make_shared<PacketPlayerListItem>(PacketPlayerListItem::Type::REMOVE_PLAYER, this);
    for (EntityPlayer *const &player : Server::getPlayers())
        player->sendPacket(packet);
}

std::shared_ptr<ServerPacket> EntityPlayer::getSpawnPacket() {
    return std::make_shared<PacketSpawnPlayer>(std::dynamic_pointer_cast<EntityPlayer>(shared_from_this()));
}

void EntityPlayer::onChunk(std::shared_ptr<Chunk> oldChunk, std::shared_ptr<Chunk> newChunk) {
    oldChunk->removePlayer(std::dynamic_pointer_cast<EntityPlayer>(shared_from_this()));
    newChunk->addPlayer(std::dynamic_pointer_cast<EntityPlayer>(shared_from_this()));
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++)
            if (newChunk->getX() + x < oldChunk->getX() - VIEW_DISTANCE
                || newChunk->getX() + x > oldChunk->getX() + VIEW_DISTANCE
                || newChunk->getZ() + z < oldChunk->getZ() - VIEW_DISTANCE
                || newChunk->getZ() + z > oldChunk->getZ() + VIEW_DISTANCE) {
                std::shared_ptr<Chunk> chunk = world->getChunk(newChunk->getX() + x, newChunk->getZ() + z);
                sendPacket(std::make_shared<PacketChunkData>(chunk, false));
                std::shared_ptr<PacketSpawnPlayer> packet = std::make_shared<PacketSpawnPlayer>(
                    std::dynamic_pointer_cast<EntityPlayer>(shared_from_this()));
                for (std::shared_ptr<EntityPlayer> player : chunk->getPlayers())
                    if (player.get() != this) {
                        sendPacket(std::make_shared<PacketSpawnPlayer>(player));
                        player->sendPacket(packet);
                    }
            }
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; x++)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; z++)
            if (oldChunk->getX() + x < newChunk->getX() - VIEW_DISTANCE
                || oldChunk->getX() + x > newChunk->getX() + VIEW_DISTANCE
                || oldChunk->getZ() + z < newChunk->getZ() - VIEW_DISTANCE
                || oldChunk->getZ() + z > newChunk->getZ() + VIEW_DISTANCE) {
                std::shared_ptr<Chunk> chunk = world->getChunk(oldChunk->getX() + x, oldChunk->getZ() + z);
                sendPacket(std::make_shared<PacketChunkData>(chunk, true));
                std::unordered_set<varint_t> entitiesIds;
                std::shared_ptr<PacketDestroyEntities> packet = std::make_shared<PacketDestroyEntities>(getEntityId());
                for (std::shared_ptr<EntityPlayer> player : chunk->getPlayers())
                    if (player.get() != this) {
                        entitiesIds.insert(player->getEntityId());
                        player->sendPacket(packet);
                    }
                if (!entitiesIds.empty())
                    sendPacket(std::make_shared<PacketDestroyEntities>(entitiesIds));
            }
}

void EntityPlayer::onTick() {
    EntityLiving::onTick();
    std::vector<std::shared_ptr<Entity>> entities = world->getEntityCollisions(boundingBox.clone().expand(1, 0.5, 1),
    [this] (std::shared_ptr<Entity> entity) {
        return entity.get() != this;
    });
    for (std::shared_ptr<Entity> entity : entities)
        entity->onCollision(std::dynamic_pointer_cast<EntityPlayer>(shared_from_this()));
}
