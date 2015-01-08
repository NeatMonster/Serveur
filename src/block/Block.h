#ifndef __Serveur__Block__
#define __Serveur__Block__

#include "Types.h"

#include <unordered_map>

class Block {
public:
    static void registerBlock(ubyte_t, string_t, Block*);

    static void registerBlocks();

    static Block *getBlock(ubyte_t);

    static Block *getBlock(string_t);

    static ubyte_t getBlockId(string_t);

    static string_t getBlockName(ubyte_t);

    Block();

private:
    static std::unordered_map<ubyte_t, string_t> idToName;
    static std::unordered_map<ubyte_t, Block*> idToBlock;
    static std::unordered_map<string_t, ubyte_t> nameToId;
    static std::unordered_map<string_t, Block*> nameToBlock;
};

#endif /* defined(__Serveur__Block__) */
