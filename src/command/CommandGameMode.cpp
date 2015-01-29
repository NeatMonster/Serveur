#include "CommandGameMode.h"

#include "ChatMessage.h"
#include "EntityPlayer.h"
#include "Logger.h"
#include "StringUtils.h"
#include "Types.h"

CommandGameMode::CommandGameMode() : Command("gamemode", "Change le gamemode d'un joueur", {"gm"}) {}

void CommandGameMode::perform(CommandSender *sender, std::vector<string_t> args) {
    if (args.size() == 1) {
        EntityPlayer *player = dynamic_cast<EntityPlayer*>(sender);
        if (player == nullptr)
            throw CommandException("Cette commande est pour les joueurs uniquement.");
        int_t gameMode = StringUtils::fromString<int_t>(args[0]);
        if (gameMode < EntityPlayer::GameMode::SURVIVAL || gameMode > EntityPlayer::GameMode::SPECTATOR)
            gameMode = EntityPlayer::GameMode::SURVIVAL;
        player->setGameMode((EntityPlayer::GameMode) gameMode);
        player->sendMessage(Chat() << Color::YELLOW << "Votre mode de jeu a été changé");
        Logger() << "[" << player->getName() << " : " << "Mode de jeu changé en " << gameMode << "]" << std::endl;
    } else
        throw WrongUsageException("/gamemode <mode>");
}
