#include "PacketHandler.h"

#include "PacketHandshake.h"
#include "PacketLoginStart.h"
#include "PacketLoginSuccess.h"
#include "PlayerConnection.h"

#include "polarssl/md5.h"

#include <iomanip>
#include <sstream>

PacketHandler::PacketHandler(PlayerConnection *connect) : connect(connect) {}

void PacketHandler::handleHandshake(PacketHandshake *packet) {
    switch (packet->nextState) {
        case PlayerConnection::LOGIN:
            if (packet->protocolVersion < 47)
                connect->disconnect("Client trop ancien, merci d'utiliser au moins la 1.8");
            else if (packet->protocolVersion > 47)
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
    PacketLoginSuccess *successPacket = new PacketLoginSuccess();
    successPacket->username = name;
    successPacket->uuid = uuid;
    connect->sendPacket(successPacket);
    connect->phase = PlayerConnection::PLAY;
    std::cout << uuid << std::endl;
}
