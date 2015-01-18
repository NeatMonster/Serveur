#ifndef __Serveur__Block__
#define __Serveur__Block__

#include "Types.h"

#include <unordered_map>

class Block {
public:
    static void registerBlock(ubyte_t, string_t, Block*);

    static void registerBlocks();

    static void deRegisterBlocks();

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

public:
    /*
     * !NE PAS SUPPRIMER CE COMMENTAIRE!
     * Ici en commentaire les classes des Blocks dans le server original. Il faudra les mettre à la place de "Block" quand ces classes seront implémentées.
     * Si pas de commentaire, la classe doit rester Block.
     */
    static Block air;
    static Block stone;
    static Block grass; //BlockGrass
    static Block dirt;
    static Block cobblestone;
    static Block planks;
    static Block sapling;
    static Block bedrock;
    static Block flowing_water; //BlockDynamicFluid
    static Block water; //BlockStaticLiquid
    static Block flowing_lava; //BlockDynamicLiquid
    static Block lava; //BlockStaticLiquid
    static Block sand;
    static Block gravel;
    static Block gold_ore;
    static Block iron_ore;
    static Block coal_ore;
    static Block log;
    static Block leaves; //BlockLeaves
    static Block sponge;
    static Block glass;
    static Block lapis_ore;
    static Block lapis_block;
    static Block dispenser;
    static Block sandstone;
    static Block noteblock;
    static Block bed;
    static Block golden_rail;
    static Block detector_rail;
    static Block sticky_piston; //BlockPistonBase
    static Block web;
    static Block tallgrass; //BlockTallGrass
    static Block deadbush; //BlockDeadBush
    static Block piston; //BlockPistonBase
    static Block piston_head; //BlockPistonExtension
    static Block wool;
    static Block piston_extension; //BlockPistonMoving
    static Block yellow_flower; //BlockFlower
    static Block red_flower; //BlockFlower
    static Block brown_mushroom; //BlockBush
    static Block red_mushroom; //BlockBush
    static Block gold_block;
    static Block iron_block;
    static Block double_stone_slab; //BlockSlab
    static Block stone_slab; //BlockSlab
};

#endif /* defined(__Serveur__Block__) */
