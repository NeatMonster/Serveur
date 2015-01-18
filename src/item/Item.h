#ifndef __Serveur__Item__
#define __Serveur__Item__

#include "Types.h"

#include <unordered_map>

class Item {
public:
    static void registerItem(ushort_t, string_t, Item*);

    static void registerItems();

    static void deRegisterItems();

    static Item *getItem(ubyte_t);

    static Item *getItem(string_t);

    static ushort_t getItemId(string_t);

    static string_t getItemName(ushort_t);

    Item();

private:
    static std::unordered_map<ushort_t, string_t> idToName;
    static std::unordered_map<ushort_t, Item*> idToItem;
    static std::unordered_map<string_t, ushort_t> nameToId;
    static std::unordered_map<string_t, Item*> nameToItem;

protected:
    int maxStackSize = 64;
    int maxDamage;
};

#endif /* defined(__Serveur__Item__) */
