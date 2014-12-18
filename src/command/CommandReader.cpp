#include "CommandReader.h"

#include "Types.h"

#include <iostream>

CommandReader::CommandReader(CommandQueue *commands) : commands(commands) {
    thread = std::thread(&CommandReader::run, this);
}

void CommandReader::run() {
    while (true) {
        string_t command;
        std::getline(std::cin, command);
        commands->push(command);
    }
}
