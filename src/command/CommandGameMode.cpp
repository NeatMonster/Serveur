#include "CommandGameMode.h"

#include "ChatMessage.h"
#include "EntityPlayer.h"
#include "Logger.h"
#include "StringUtils.h"
#include "Types.h"


CommandGameMode::CommandGameMode()
: Command("gamemode", "Change le gamemode d'un joueur", {"gamemode", "gm"})
{}

void CommandGameMode::perform(CommandSender *sender, std::vector<string_t> args) {

    if (args.size() != 1) {
        throw WrongUsageException("/gamemode [gamemode]");
    }
    else {
        EntityPlayer *player = dynamic_cast<EntityPlayer*>(sender);
        if (player == nullptr)
            throw CommandException("Cette commande est pour les joueurs uniquement.");

        int_t gamemode = StringUtils::FromString<int_t>(args[0]);
        if ( gamemode < static_cast<int_t>(EntityPlayer::GameMode::SURVIVAL) || gamemode > static_cast<int_t>(EntityPlayer::GameMode::SPECTATOR) )
        {
            std::stringstream message;
            message << "Valeur (" << gamemode << ") invalide pour la commande gamemode";
            throw CommandException(message.str());
        }

        player->setGameMode((EntityPlayer::GameMode)gamemode);

        std::stringstream logMessage;
        logMessage << "player " << player->getName() << " (id: " << player->getEntityId() << ") set to gamemode " << gamemode;
        Logger() << logMessage.str() << std::endl;

        std::stringstream ssMessage;
        ssMessage<< "gamemode modifié (" << gamemode << ")";
        ChatMessage messageSentToPLayer;
        messageSentToPLayer << ssMessage.str();
        player->sendMessage(messageSentToPLayer);
    }
}
