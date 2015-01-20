#include "CommandGameMode.h"

#include "EntityPlayer.h"
#include "StringUtils.h"
#include "Types.h"

CommandGameMode::CommandGameMode()
: Command("server", "Change le gamemode d'un joueur", {"gamemode"})
{};

void CommandGameMode::perform(CommandSender *sender, std::vector<string_t> args) {
    if (args.size() == 0) {
        throw WrongUsageException("/gamemode [gamemode]");
    } else if (args.size()!=2) {
        EntityPlayer *player = dynamic_cast<EntityPlayer*>(sender);
        if (player == nullptr)
            throw CommandException("Cette commande est pour les joueurs uniquement.");

        int_t gameModeAsInt = StringUtils::FromString<int_t>(args[1]);
        if ( gameModeAsInt<0 || gameModeAsInt>3 )
            throw WrongUsageException("/gamemode [gamemode]");

        player->setGameMode((EntityPlayer::GameMode)gameModeAsInt);

    } else
        throw WrongUsageException("/gamemode [gamemode]");
}
