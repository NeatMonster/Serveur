#include "CommandStop.h"

#include "Server.h"

CommandStop::CommandStop() : Command("stop", "Eteins le serveur", {}) {};

void CommandStop::perform(CommandSender*, std::vector<string_t>) {
    Server::getServer()->stop();
}
