#include "CommandManager.h"

#include "ChatMessage.h"
#include "CommandStop.h"
#include "Server.h"

#include <algorithm>
#include <sstream>
#include <vector>

CommandManager::CommandManager() {
    reader = new CommandReader(&queue);
    registerCommand(new CommandStop());
};

CommandManager::~CommandManager() {
    delete reader;
    for (auto command : commands)
        delete command.second;
};

void CommandManager::registerCommand(Command *command) {
    commands[command->getName()] = command;
    for (string_t alias : command->getAliases())
        commands[alias] = command;
}

void CommandManager::processCommand(string_t s, CommandSender *sender) {
    string_t arg;
    std::vector<string_t> args;
    std::istringstream ss(s, std::istringstream::in);
    while (ss >> arg)
        args.push_back(arg);
    string_t name = args[0];
    args.erase(args.begin());
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    if (commands.find(name) == commands.end())
        sender->sendMessage(Chat() << "Commande inconnue. Essayez /help pour une liste des commandes.");
    else
        try {
            commands[name]->perform(sender, args);
        } catch (const Command::WrongUsageException &e) {
            sender->sendMessage(Chat() << Color::RED << "Usage : " << e.what());
        } catch (const Command::CommandException &e) {
            sender->sendMessage(Chat() << Color::RED << "Erreur : " << e.what());
        }
}

void CommandManager::handleCommands() {
    string_t command;
    while (queue.tryPop(&command))
        processCommand(command, Server::getServer());
}
