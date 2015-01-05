#include "ConfigManager.h"

#include "json11/json11.hpp"

#include <fstream>
#include <sstream>

ConfigManager::ConfigManager() {
    load();
}

void ConfigManager::load() {
    std::ifstream input("config.json");
    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();
    string_t err;
    json11::Json config = json11::Json::parse(buffer.str(), err);
    if (config["serverIP"].is_string())
        serverIP = config["serverIP"].string_value();
    if (config["serverPort"].is_number())
        serverPort = config["serverPort"].number_value();
    save();
}

void ConfigManager::save() {
    std::ofstream output("config.json");
    json11::Json config = json11::Json::object {
        {"serverIP", serverIP},
        {"serverPort", serverPort}
    };
    output << config.dump();
    output.close();
}

string_t ConfigManager::getServerIP() {
    return serverIP;
}

ushort_t ConfigManager::getServerPort() {
    return serverPort;
}
