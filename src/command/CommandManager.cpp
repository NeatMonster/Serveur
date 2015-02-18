#include "CommandManager.h"

#include "ChatMessage.h"
#include "CommandGameMode.h"
#include "CommandServer.h"
#include "CommandStop.h"
#include "Logger.h"
#include "Server.h"

#include <algorithm>
#include <sstream>
#include <vector>

CommandManager::CommandManager() {
    reader = new CommandReader(&queue);
    registerCommand(new CommandGameMode());
    registerCommand(new CommandServer());
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
        aliases[alias] = command;
}

void CommandManager::processCommand(string_t s, CommandSender *sender) {
    string_t arg;
    std::vector<string_t> args;
    std::istringstream ss(s, std::istringstream::in);
    while (ss >> arg)
        args.push_back(arg);
    if (args.empty())
        return;
    string_t name = args[0];
    args.erase(args.begin());
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    if (name == "help")
        performHelp(sender);
    else if (commands.find(name) == commands.end() && aliases.find(name) == aliases.end())
        sender->sendMessage(Chat() << "Commande inconnue. Essayez /help pour une liste des commandes.");
    else
        try {
            if(commands.find(name) != commands.end())
                commands[name]->perform(sender, args);
            else
                aliases[name]->perform(sender,args);
        } catch (const Command::WrongUsageException &e) {
            sender->sendMessage(Chat() << Color::RED << "Usage : " << e.what());
        } catch (const Command::CommandException &e) {
            sender->sendMessage(Chat() << Color::RED << "Une erreur est survenue lors de l'exécution de la commande.");
            sender->sendMessage(Chat() << Color::RED << e.what());
        }
}

void CommandManager::performHelp(CommandSender *sender) {
    //TODO Gérer plusieurs pages
    sender->sendMessage(Chat() << "--- Affichage de la page 1 sur 1 ---");
    for (std::map<string_t,Command*>::iterator it = commands.begin(); it != commands.end(); ++it)
        sender->sendMessage(Chat() << ChatMessage::Style::BOLD << it->second->getName()
                            << ChatMessage::Style::RESET << " : " << it->second->getDescription());
}

void CommandManager::handleCommands() {
    string_t command;
    while (queue.tryPop(&command))
        processCommand(command, Server::getServer());
}
