#include "CommandGameMode.h"

#include "EntityPlayer.h"
#include "PacketPluginMessage.h"

CommandGameMode::CommandGameMode() : Command("server", "Change le gamemode d'un joueur", {}) {};

void CommandGameMode::perform(CommandSender *sender, std::vector<string_t> args) {
    if (args.size() == 0) {
        throw WrongUsageException("/gamemode [gamemode]");
    } else if (args.size() == 1) {
        EntityPlayer *player = dynamic_cast<EntityPlayer*>(sender);
        if (player == nullptr)
            throw CommandException("Cette commande est pour les joueurs uniquement.");
        PacketPluginMessage *packet = new PacketPluginMessage();
        packet->channel = "MF|Connect";
        PacketBuffer buffer;
        buffer.putString(args[0]);
        packet->data = ubytes_t(buffer.getArray(), buffer.getArray() + buffer.getLimit());
        player-> sendPacket(packet);
    } else
        throw WrongUsageException("/gamemode [gamemode]");
}
