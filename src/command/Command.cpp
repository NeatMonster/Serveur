#include "Command.h"

Command::Command(string_t name, std::vector<string_t> aliases) : name(name), aliases(aliases) {};

Command::~Command() {}

string_t Command::getName() {
    return name;
}

std::vector<string_t > Command::getAliases() {
    return std::vector<string_t>();
}
