#include "PacketHandler.h"

#include "Logger.h"
#include "PacketChatMessage.h"
#include "PacketHandshake.h"
#include "PacketLoginStart.h"
#include "PacketLoginSuccess.h"
#include "Player.h"
#include "PlayerConnection.h"
#include "Server.h"

#include "polarssl/md5.h"

#include <iomanip>
#include <sstream>

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
    for (Player *player : Server::getPlayers())
        if (player->getUUID() == uuid)
            player->disconnect("Vous êtes connecté depuis un autre emplacement");
    connect->phase = PlayerConnection::PLAY;
    Player *player = new Player(Server::getWorld(), connect);
    connect->player = player;
    Logger::info() << player->getName() << " [/" << player->getIP() << ":" << player->getPort()
        << "] s'est connecté avec l'ID d'entité " << player->getEntityId()
        << " en (" << player->getX() << ", " << player->getY() << ", " << player->getZ() << ")" << std::endl;
}

void PacketHandler::handleChatMessage(PacketChatMessage *packet) {
    Server::broadcast(Chat() << "<" << connect->getName() << "> " << packet->message);
}
