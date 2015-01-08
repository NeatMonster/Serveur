#include "PacketHandler.h"

#include "Logger.h"
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
#include "Player.h"
#include "PlayerConnection.h"
#include "Server.h"

#include "polarssl/md5.h"

#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std::chrono;
typedef std::chrono::high_resolution_clock Clock;

PacketHandler::PacketHandler(PlayerConnection *connect) : connect(connect), profile(nullptr) {}

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
    profile = Server::getDatabase()->getProfile(packet->name);
    connect->sendPacket(new PacketLoginSuccess(profile->getUUID(), profile->getName()));
    for (Player *const &player : Server::getPlayers())
        if (player->getUUID() == profile->getUUID())
            player->disconnect("Vous êtes connecté depuis un autre emplacement");
    connect->phase = PlayerConnection::PLAY;
    Player *player = new Player(Server::getServer()->getWorld(), connect);
    connect->player = player;
    Logger() << player->getName() << " [/" << player->getIP() << ":" << player->getPort()
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
    connect->player->onGround = packet->onGround;
    connect->player->rotate(packet->yaw, packet->pitch);
}

void PacketHandler::handlePlayerPosition(PacketPlayerPosition *packet) {
    connect->player->onGround = packet->onGround;
    connect->player->move(packet->x, packet->y, packet->z);
}

void PacketHandler::handlePlayerPositionLook(PacketPlayerPositionLook *packet) {
    connect->player->onGround = packet->onGround;
    connect->player->move(packet->x, packet->y, packet->z);
    connect->player->rotate(packet->yaw, packet->pitch);
}

void PacketHandler::handleAnimation(PacketAnimation*) {
    for (Player *const &watcher : connect->player->getWatchers())
        watcher->sendPacket(new PacketAnimation(connect->player->getEntityId(), 0));
}

void PacketHandler::handleCreativeInventoryAction(PacketCreativeInventoryAction *packet) {
    if(packet->slot == -1) {
        //TODO Gérer le drop
    } else if (packet->stack == nullptr) {
        connect->player->getInventory().putStack(packet->slot, nullptr);
    } else
        connect->player->getInventory().putStack(packet->slot, packet->stack->clone());
}
