#include "CommandServer.h"

#include "EntityPlayer.h"
#include "PacketPluginMessage.h"

CommandServer::CommandServer() : Command("server", "Transfert le joueur vers un serveur", {}) {};

void CommandServer::perform(CommandSender *sender, std::vector<string_t> args) {
    if (args.size() == 0) {
        EntityPlayer *player = dynamic_cast<EntityPlayer*>(sender);
        if (player == nullptr)
            throw CommandException("Cette commande est pour les joueurs uniquement.");
        PacketPluginMessage *packet = new PacketPluginMessage();
        packet->channel = "MF|GetServers";
        player->sendPacket(packet);
    } else if (args.size() == 1) {
        EntityPlayer *player = dynamic_cast<EntityPlayer*>(sender);
        if (player == nullptr)
            throw CommandException("Cette commande est pour les joueurs uniquement.");
        PacketPluginMessage *packet = new PacketPluginMessage();
        packet->channel = "MF|Connect";
        PacketBuffer buffer;
        buffer.putString(args[0]);
        packet->data = ubytes_t(buffer.getArray(), buffer.getArray() + buffer.getLimit());
        player->sendPacket(packet);
    } else
        throw WrongUsageException("/server [serveur]");
}
