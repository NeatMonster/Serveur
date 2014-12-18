#include "CommandStop.h"

#include "Server.h"

CommandStop::CommandStop() : Command("stop", {}) {};

void CommandStop::perform(CommandSender*, std::vector<string_t>) {
    Server::getServer()->stop();
}
