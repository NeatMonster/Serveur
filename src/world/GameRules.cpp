#include "GameRules.h"

#include <sstream>

typedef std::pair<string_t, GameRules::ValueType> valuePair;

GameRules::GameRules() {
    addGameRule("doFireTick", "true", ValueType::BOOLEAN_VALUE);
    addGameRule("mobGriefing", "true", ValueType::BOOLEAN_VALUE);
    addGameRule("keepInventory", "false", ValueType::BOOLEAN_VALUE);
    addGameRule("doMobSpawning", "true", ValueType::BOOLEAN_VALUE);
    addGameRule("doMobLoot", "true", ValueType::BOOLEAN_VALUE);
    addGameRule("doTileDrops", "true", ValueType::BOOLEAN_VALUE);
    addGameRule("commandBlockOutput", "true", ValueType::BOOLEAN_VALUE);
    addGameRule("naturalRegeneration", "true", ValueType::BOOLEAN_VALUE);
    addGameRule("doDaylightCycle", "true", ValueType::BOOLEAN_VALUE);
    addGameRule("logAdminCommands", "true", ValueType::BOOLEAN_VALUE);
    addGameRule("showDeathMessages", "true", ValueType::BOOLEAN_VALUE);
    addGameRule("randomTickSpeed", "3", ValueType::NUMERICAL_VALUE);
    addGameRule("sendCommandFeedback", "true", ValueType::BOOLEAN_VALUE);
    addGameRule("reducedDebugInfo", "false", ValueType::BOOLEAN_VALUE);
}

void GameRules::addGameRule(string_t key, string_t value, ValueType type) {
    rules[key] = valuePair(value, type);
}

int_t GameRules::getGameRuleNumericalValue(string_t key) {
    std::map<string_t, valuePair>::iterator it = rules.find(key);
    if(it == rules.end())
        return 0;
    if(it->second.second == ValueType::NUMERICAL_VALUE) {
        int_t value;
        std::istringstream(it->second.first) >> value;
        return value;
    }
    else
        return 0;
}

bool GameRules::getGameRuleBooleanValue(string_t key) {
    std::map<string_t, valuePair>::iterator it = rules.find(key);
    if(it == rules.end())
        return false;
    if(it->second.second == ValueType::BOOLEAN_VALUE) {
        return it->second.first == "true";
    }
    else
        return false;
}
