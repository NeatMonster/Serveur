#include "CommandServer.h"

#include "PacketPluginMessage.h"
#include "Player.h"

CommandServer::CommandServer() : Command("server", "Transfert le joueur vers un serveur", {}) {};

void CommandServer::perform(CommandSender *sender, std::vector<string_t> args) {
    if (args.size() == 0) {
        Player *player = dynamic_cast<Player*>(sender);
        if (player == nullptr)
            throw CommandException("Cette commande est pour les joueurs uniquement.");
        PacketPluginMessage *packet = new PacketPluginMessage();
        packet->channel = "MF|GetServers";
        player->sendPacket(packet);
    } else if (args.size() == 1) {
        //TODO Implémenter le changement de serveur
    } else
        throw WrongUsageException("/server [serveur]");
}
