#include "Command.h"

Command::Command(string_t name, std::vector<string_t> aliases, string_t description) : name(name), aliases(aliases), description(description) {};

Command::~Command() {}

string_t Command::getName() {
    return name;
}

string_t Command::getDescription() {
    return description;
}

std::vector<string_t > Command::getAliases() {
    return std::vector<string_t>();
}
