#ifndef __Serveur__GameRules__
#define __Serveur__GameRules__

#include "Types.h"

#include <map>

class GameRules
{
    public:
        enum ValueType {ANY_VALUE, BOOLEAN_VALUE, NUMERICAL_VALUE};

        GameRules();

        void addGameRule(string_t, string_t, ValueType);

        int_t getGameRuleNumericalValue(string_t);

        bool getGameRuleBooleanValue(string_t);

    private:
        std::map<string_t, std::pair<string_t, ValueType> > rules;
};

#endif // __Serveur__GameRules__
