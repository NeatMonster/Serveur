#include "PacketHandler.h"

#include "EntityItem.h"
#include "EntityPlayer.h"
#include "InventoryPlayer.h"
#include "Level.h"
#include "Logger.h"
#include "MathUtils.h"
#include "PacketAnimation.h"
#include "PacketChatMessage.h"
#include "PacketCreativeInventoryAction.h"
#include "PacketHandshake.h"
#include "PacketKeepAlive.h"
#include "PacketLoginStart.h"
#include "PacketLoginSuccess.h"
#include "PacketPlayer.h"
#include "PacketPlayerLook.h"
#include "PacketPlayerPosition.h"
#include "PacketPlayerPositionLook.h"
#include "PacketPluginMessage.h"
#include "PlayerConnection.h"
#include "Server.h"
#include "World.h"

#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std::chrono;
typedef std::chrono::high_resolution_clock Clock;

PacketHandler::PacketHandler(PlayerConnection *connect) : connect(connect) {}

void PacketHandler::handleHandshake(PacketHandshake *packet) {
    switch (packet->nextState) {
        case PlayerConnection::LOGIN:
            if (packet->protocol < 47)
                connect->disconnect("Client trop ancien, merci d'utiliser au moins la 1.8");
            else if (packet->protocol > 47)
                connect->disconnect("Serveur trop ancien, merci d'utiliser au plus la 1.8.1");
            else
                connect->phase = PlayerConnection::LOGIN;
            break;
        default:
            connect->disconnect("État invalide : " + std::to_string(packet->nextState));
            break;
    }
}

void PacketHandler::handleLoginStart(PacketLoginStart *packet) {
    Profile *profile = Server::getDatabase()->getProfile(packet->name);
    connect->profile = profile;
    connect->sendPacket(std::make_shared<PacketLoginSuccess>(profile->getUUID(), profile->getName()));
    for (EntityPlayer *player : Server::getPlayers())
        if (player->getUUID() == profile->getUUID())
            player->disconnect("Vous êtes connecté depuis un autre emplacement");
    connect->phase = PlayerConnection::PLAY;
    World *world = Server::getServer()->getWorld();
    std::shared_ptr<EntityPlayer> player = std::make_shared<EntityPlayer>(world, connect);
    Position spawn = world->getLevel()->getSpawn();
    player->setPosition(spawn.x, spawn.y, spawn.z);
    world->addEntity(player->getEntityId(), player);
    player->getInventory().sendContent();
    connect->player = player.get();
    Logger() << player->getName() << " [/" << player->getConnection()->getIP() << ":" << player->getConnection()->getPort()
        << "] s'est connecté avec l'ID d'entité " << player->getEntityId()
        << " en (" << player->getX() << ", " << player->getY() << ", " << player->getZ() << ")" << std::endl;
}

void PacketHandler::handleKeepAlive(PacketKeepAlive *packet) {
    if (packet->keepAliveId == Server::getNetwork()->getKeepAliveId()) {
        connect->rcvdKeepAlive = Clock::now();
        milliseconds elapsed = duration_cast<milliseconds>(connect->rcvdKeepAlive - connect->sentKeepAlive);
        if (connect->ping > 0)
            connect->ping = (3 * connect->ping + elapsed.count()) / 4;
        else
            connect->ping = elapsed.count();
    }
}

void PacketHandler::handleChatMessage(PacketChatMessage *packet) {
    if (packet->message[0] == '/')
        Server::getCommands()->processCommand(packet->message.substr(1), connect->player);
    else
        Server::broadcast(Chat() << "<" << connect->getName() << "> " << packet->message);
}

void PacketHandler::handlePluginMessage(PacketPluginMessage *packet) {
    if (packet->channel == "MF|GetServers") {
        PacketBuffer buffer;
        buffer.putUBytes(packet->data);
        buffer.setPosition(0);
        varint_t size;
        buffer.getVarInt(size);
        string_t server, servers = "Liste des serveurs : ";
        for (size_t i = 0; i < size; i++) {
            buffer.getString(server);
            if (i > 0)
                servers += ", ";
            servers += server;
        }
        servers += ".";
        connect->player->sendMessage(Chat() << Color::YELLOW << servers);
    } else if (packet->channel == "MF|Connect") {
        PacketBuffer buffer;
        buffer.putUBytes(packet->data);
        buffer.setPosition(0);
        string_t message;
        buffer.getString(message);
        connect->player->sendMessage(Chat() << Color::RED << "Une erreur est survenue lors de l'exécution de la commande.");
        connect->player->sendMessage(Chat() << Color::RED << message);
    }
}

void PacketHandler::handlePlayer(PacketPlayer *packet) {
    connect->player->onGround = packet->onGround;
}

void PacketHandler::handlePlayerLook(PacketPlayerLook *packet) {
    handleRotation(packet->yaw, packet->pitch);
}

void PacketHandler::handlePlayerPosition(PacketPlayerPosition *packet) {
    handlePosition(packet->x, packet->y, packet->z, packet->onGround);
}

void PacketHandler::handlePlayerPositionLook(PacketPlayerPositionLook *packet) {
    handlePosition(packet->x, packet->y, packet->z, packet->onGround);
    handleRotation(packet->yaw, packet->pitch);
}

void PacketHandler::handleAnimation(PacketAnimation*) {
    std::shared_ptr<PacketAnimation> packet = std::make_shared<PacketAnimation>(connect->player->getEntityId(), 0);
    for (EntityPlayer *watcher : connect->player->getWatchers())
        watcher->sendPacket(packet);
}

void PacketHandler::handleCreativeInventoryAction(PacketCreativeInventoryAction *packet) {
    if (connect->player->getGameMode() == EntityPlayer::GameMode::CREATIVE) {
        bool valid = packet->stack != nullptr && packet->stack->getItem() != nullptr && packet->stack->getCount() > 0
            && packet->stack->getCount() <= 64 && packet->stack->getDamage() >= 0;
        if (packet->slot == -1 && valid)
            connect->player->drop(packet->stack);
        else if (packet->slot >= 9 && packet->slot <= 44 && (packet->stack == nullptr || valid))
            connect->player->getInventory().putItemStack(packet->slot, packet->stack);
    }
}

void PacketHandler::handleRotation(float_t yaw, float_t pitch) {
    connect->player->setRotation(yaw, pitch);
    connect->player->setHeadRotation(yaw);
}

void PacketHandler::handlePosition(double_t x, double_t y, double_t z, bool onGround) {
    EntityPlayer *player = connect->player;
    double_t moveX = x - player->posX;
    double_t moveY = y - player->posY;
    double_t moveZ = z - player->posZ;
    player->move(moveX, moveY, moveZ);
    player->onGround = onGround;
    if (player->onGround && moveY > 0)
        player->jump();
}
