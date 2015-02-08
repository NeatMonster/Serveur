#include "EntityPlayer.h"

#include "Chunk.h"
#include "EntityItem.h"
#include "Level.h"
#include "MathUtils.h"
#include "PacketChangeGameState.h"
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
#include "PacketUpdateHealth.h"
#include "PlayerConnection.h"
#include "Server.h"
#include "World.h"

#include <cmath>

EntityPlayer::EntityPlayer(World *world, PlayerConnection *connect) : EntityLiving(world), connect(connect),
        inventory(this), container(inventory, this), openContainer(container), gameMode(CREATIVE) {
    uuid = connect->getProfile()->getUUID();
    name = connect->getProfile()->getName();
    setSize(0.6, 1.8);
    lastHealth = -1.0E8F;
    lastFoodLevel = -99999999;
    wasHungry = true;
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

ContainerPlayer &EntityPlayer::getContainer() {
    return container;
}

InventoryPlayer &EntityPlayer::getInventory() {
    return inventory;
}

EntityPlayer::GameMode EntityPlayer::getGameMode() {
    return gameMode;
}

PlayerCapabilities &EntityPlayer::getCapabilities() {
    return capabilities;
}

FoodStats& EntityPlayer::getFoodStats() {
    return foodStats;
}

bool EntityPlayer::shouldHeal() {
    return getHealth() > 0.0F && getHealth() < getMaxHealth();
}

bool EntityPlayer::canEat(bool value) {
    return (value || foodStats.needFood()) && !capabilities.disableDamage;
}

void EntityPlayer::addExhaustion(float value) {
    if(!capabilities.disableDamage)
        foodStats.addExhaustion(value);
}

void EntityPlayer::jump() {
    if(isSprinting())
        addExhaustion(0.8F);
    else
        addExhaustion(0.2F);
}

void EntityPlayer::setGameMode(EntityPlayer::GameMode gameMode) {
    this->gameMode = gameMode;
    std::shared_ptr<PacketPlayerListItem> listPacket =
        std::make_shared<PacketPlayerListItem>(PacketPlayerListItem::Type::UPDATE_GAMEMODE, this);
    for (EntityPlayer *player : Server::getPlayers())
        player->sendPacket(listPacket);
    std::shared_ptr<PacketChangeGameState> statePacket = std::make_shared<PacketChangeGameState>();
    statePacket->reason = 3;
    statePacket->value = gameMode;
    sendPacket(statePacket);
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
    world->addEntity(entity->getEntityId(), entity);
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

    std::set<EntityPlayer*> players = Server::getPlayers();
    std::shared_ptr<PacketPlayerListItem> listPacket =
        std::make_shared<PacketPlayerListItem>(PacketPlayerListItem::Type::ADD_PLAYER, this);
    for (EntityPlayer *player : players)
        if (player != this)
            player->sendPacket(listPacket);
    players.insert(this);
    sendPacket(std::make_shared<PacketPlayerListItem>(PacketPlayerListItem::Type::ADD_PLAYER, players));

    std::shared_ptr<PacketPlayerPositionLook> posPacket = std::make_shared<PacketPlayerPositionLook>();
    posPacket->x = posX;
    posPacket->y = posY;
    posPacket->z = posZ;
    posPacket->yaw = rotYaw;
    posPacket->pitch = rotPitch;
    posPacket->flags = 0;
    sendPacket(posPacket);

    sendPacket(std::make_shared<PacketTimeUpdate>(world->getLevel()->getTime(), world->getLevel()->getDayTime()));

    container.onCraftGuiOpened(this);

    int_t xChunk = (int_t) floor(posX) >> 4;
    int_t zChunk = (int_t) floor(posZ) >> 4;
    std::vector<Chunk*> chunks = {world->getChunk(xChunk, zChunk)};
    for (int_t distance = 1; distance <= VIEW_DISTANCE; ++distance) {
        for (int_t x = -distance; x < distance; ++x)
            chunks.push_back(world->getChunk(xChunk + x, zChunk - distance));
        for (int_t z = -distance; z < distance; ++z)
            chunks.push_back(world->getChunk(xChunk + distance, zChunk + z));
        for (int_t x = distance; x > -distance; x--)
            chunks.push_back(world->getChunk(xChunk + x, zChunk + distance));
        for (int_t z = distance; z > -distance; z--)
            chunks.push_back(world->getChunk(xChunk - distance, zChunk + z));
    }
    std::vector<Chunk*> packetChunks;
    for (Chunk *chunk : chunks) {
        if (packetChunks.size() == 10) {
            sendPacket(std::make_shared<PacketMapChunkBulk>(packetChunks));
            for (Chunk *packetChunk : packetChunks)
                for (EntityPlayer *player : packetChunk->getPlayers())
                    if (player != this)
                        sendPacket(std::make_shared<PacketSpawnPlayer>(player));
            packetChunks.clear();
        }
        packetChunks.push_back(chunk);
    }
    if (!packetChunks.empty()) {
        sendPacket(std::make_shared<PacketMapChunkBulk>(packetChunks));
        for (Chunk *packetChunk : packetChunks)
            for (EntityPlayer *player : packetChunk->getPlayers())
                if (player != this)
                    sendPacket(std::make_shared<PacketSpawnPlayer>(player));
        packetChunks.clear();
    }
}

void EntityPlayer::onQuitGame() {
    Server::broadcast(Chat() << Color::YELLOW << name << " a quitté la partie");

    std::shared_ptr<PacketPlayerListItem> packet =
        std::make_shared<PacketPlayerListItem>(PacketPlayerListItem::Type::REMOVE_PLAYER, this);
    for (EntityPlayer *player : Server::getPlayers())
        if (player != this)
            player->sendPacket(packet);
}

std::shared_ptr<ServerPacket> EntityPlayer::getSpawnPacket() {
    return std::make_shared<PacketSpawnPlayer>(this);
}

void EntityPlayer::onChunk(Chunk *oldChunk, Chunk *newChunk) {
    oldChunk->removePlayer(this);
    newChunk->addPlayer(this);
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; ++x)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; ++z)
            if (newChunk->getX() + x < oldChunk->getX() - VIEW_DISTANCE
                || newChunk->getX() + x > oldChunk->getX() + VIEW_DISTANCE
                || newChunk->getZ() + z < oldChunk->getZ() - VIEW_DISTANCE
                || newChunk->getZ() + z > oldChunk->getZ() + VIEW_DISTANCE) {
                Chunk *chunk = world->getChunk(newChunk->getX() + x, newChunk->getZ() + z);
                sendPacket(std::make_shared<PacketChunkData>(chunk, false));
                std::shared_ptr<PacketSpawnPlayer> packet = std::make_shared<PacketSpawnPlayer>(this);
                for (EntityPlayer *player : chunk->getPlayers())
                    if (player != this) {
                        sendPacket(std::make_shared<PacketSpawnPlayer>(player));
                        player->sendPacket(packet);
                    }
            }
    for (int_t x = -VIEW_DISTANCE; x <= VIEW_DISTANCE; ++x)
        for (int_t z = -VIEW_DISTANCE; z <= VIEW_DISTANCE; ++z)
            if (oldChunk->getX() + x < newChunk->getX() - VIEW_DISTANCE
                || oldChunk->getX() + x > newChunk->getX() + VIEW_DISTANCE
                || oldChunk->getZ() + z < newChunk->getZ() - VIEW_DISTANCE
                || oldChunk->getZ() + z > newChunk->getZ() + VIEW_DISTANCE) {
                Chunk *chunk = world->getChunk(oldChunk->getX() + x, oldChunk->getZ() + z);
                sendPacket(std::make_shared<PacketChunkData>(chunk, true));
                std::set<varint_t> entitiesIds;
                std::shared_ptr<PacketDestroyEntities> packet = std::make_shared<PacketDestroyEntities>(getEntityId());
                for (EntityPlayer *player : chunk->getPlayers())
                    if (player != this) {
                        entitiesIds.insert(player->getEntityId());
                        player->sendPacket(packet);
                    }
                if (!entitiesIds.empty())
                    sendPacket(std::make_shared<PacketDestroyEntities>(entitiesIds));
            }
}

void EntityPlayer::onTick() {
    EntityLiving::onTick();
    openContainer.detectAndSendChanges();
    std::vector<Entity*> entities = world->getEntityCollisions(boundingBox.clone().expand(1, 0.5, 1),
    [this] (Entity *entity) {
        return entity != this;
    });
    for (Entity *entity : entities)
        entity->onCollision(this);

    foodStats.onUpdate(this);

    if(getHealth() != lastHealth || foodStats.getFoodLevel() != lastFoodLevel || foodStats.getSaturationLevel() == 0.0F != wasHungry) {
        std::shared_ptr<PacketUpdateHealth> packet = std::make_shared<PacketUpdateHealth>();
        packet->health = getHealth();
        packet->foodLevel = foodStats.getFoodLevel();
        packet->foodSaturationLevel = foodStats.getSaturationLevel();
        sendPacket(packet);
        lastHealth = getHealth();
        lastFoodLevel = foodStats.getFoodLevel();
        wasHungry = foodStats.getSaturationLevel() == 0.0F;
    }
}
