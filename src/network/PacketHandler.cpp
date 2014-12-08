#include "PacketHandler.h"

#include "Logger.h"
#include "PacketChatMessage.h"
#include "PacketHandshake.h"
#include "PacketKeepAlive.h"
#include "PacketLoginStart.h"
#include "PacketLoginSuccess.h"
#include "PacketPlayer.h"
#include "PacketPlayerLook.h"
#include "PacketPlayerPosition.h"
#include "PacketPlayerPositionLook.h"
#include "Player.h"
#include "PlayerConnection.h"
#include "Server.h"

#include "polarssl/md5.h"

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
    name = packet->name;
    string_t s = "OfflinePlayer:" + name;
    md5_context ctx;
    md5_init(&ctx);
    md5_starts(&ctx);
    md5_update(&ctx, (ubyte_t*) s.data(), s.size());
    ubytes_t hash(16);
    md5_finish(&ctx, hash.data());
    md5_free(&ctx);
    hash[6] &= 0x0f;
    hash[6] |= 0x30;
    hash[8] &= 0x3f;
    hash[8] |= 0x80;
    std::stringstream ss;
    for (int i = 0; i < 16; i++) {
        if (i == 4 || i == 6 || i == 8 || i == 10)
            ss << "-";
        ss << std::setw(2) << std::hex << std::setfill('0') << (int) hash[i];
    }
    uuid = ss.str();
    connect->sendPacket(new PacketLoginSuccess(uuid, name));
    for (Player *const &player : Server::getPlayers())
        if (player->getUUID() == uuid)
            player->disconnect("Vous êtes connecté depuis un autre emplacement");
    connect->phase = PlayerConnection::PLAY;
    Player *player = new Player(Server::getWorld(), connect);
    connect->player = player;
    Logger::info() << player->getName() << " [/" << player->getIP() << ":" << player->getPort()
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
    Server::broadcast(Chat() << "<" << connect->getName() << "> " << packet->message);
}

void PacketHandler::handlePlayer(PacketPlayer *packet) {
    connect->player->onGround = packet->onGround;
}

void PacketHandler::handlePlayerLook(PacketPlayerLook *packet) {
    connect->player->onGround = packet->onGround;
    connect->player->setRotation(packet->yaw, packet->pitch);
}

void PacketHandler::handlePlayerPosition(PacketPlayerPosition *packet) {
    connect->player->onGround = packet->onGround;
    connect->player->setPosition(packet->x, packet->y, packet->z);
}

void PacketHandler::handlePlayerPositionLook(PacketPlayerPositionLook *packet) {
    connect->player->onGround = packet->onGround;
    connect->player->setPosition(packet->x, packet->y, packet->z);
    connect->player->setRotation(packet->yaw, packet->pitch);
}
