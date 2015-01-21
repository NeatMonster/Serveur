#ifndef __Serveur__Block__
#define __Serveur__Block__

#include "AxisAlignedBB.h"
#include "Material.h"
#include "Types.h"

#include <unordered_map>

class Block {
public:
    static Block* air;
    static Block* stone;
    static Block* grass;
    static Block* dirt;
    static Block* cobblestone;
    static Block* planks;
    static Block* sapling;
    static Block* bedrock;
    static Block* flowing_water;
    static Block* water;
    static Block* flowing_lava;
    static Block* lava;
    static Block* sand;
    static Block* gravel;
    static Block* gold_ore;
    static Block* iron_ore;
    static Block* coal_ore;
    static Block* log;
    static Block* leaves;
    static Block* sponge;
    static Block* glass;
    static Block* lapis_ore;
    static Block* lapis_block;
    static Block* dispenser;
    static Block* sandstone;
    static Block* noteblock;
    static Block* bed;
    static Block* golden_rail;
    static Block* detector_rail;
    static Block* sticky_piston;
    static Block* web;
    static Block* tallgrass;
    static Block* deadbush;
    static Block* piston;
    static Block* piston_head;
    static Block* wool;
    static Block* piston_extension;
    static Block* yellow_flower;
    static Block* red_flower;
    static Block* brown_mushroom;
    static Block* red_mushroom;
    static Block* gold_block;
    static Block* iron_block;
    static Block* double_stone_slab;
    static Block* stone_slab;
    static Block* brick_block;
    static Block* tnt;
    static Block* bookshelf;
    static Block* mossy_cobblestone;
    static Block* obsidian;
    static Block* torch;
    static Block* fire;
    static Block* mob_spawner;
    static Block* oak_stairs;
    static Block* chest;
    static Block* redstone_wire;
    static Block* diamond_ore;
    static Block* diamond_block;
    static Block* crafting_table;
    static Block* wheat;
    static Block* farmland;
    static Block* furnace;
    static Block* lit_furnace;
    static Block* standing_sign;
    static Block* wooden_door;
    static Block* ladder;
    static Block* rail;
    static Block* stone_stairs;
    static Block* wall_sign;
    static Block* lever;
    static Block* stone_pressure_plate;
    static Block* iron_door;
    static Block* wooden_pressure_plate;
    static Block* redstone_ore;
    static Block* lit_redstone_ore;
    static Block* unlit_redstone_torch;
    static Block* redstone_torch;
    static Block* stone_button;
    static Block* snow_layer;
    static Block* ice;
    static Block* snow;
    static Block* cactus;
    static Block* clay;
    static Block* reeds;
    static Block* jukebox;
    static Block* fence;
    static Block* pumpkin;
    static Block* netherrack;
    static Block* soul_sand;
    static Block* glowstone;
    static Block* portal;
    static Block* lit_pumpkin;
    static Block* cake;
    static Block* unpowered_repeater;
    static Block* powered_repeater;
    static Block* stained_glass;
    static Block* trapdoor;
    static Block* monster_egg;
    static Block* stonebrick;
    static Block* brown_mushroom_block;
    static Block* red_mushroom_block;
    static Block* iron_bars;
    static Block* glass_pane;
    static Block* melon_block;
    static Block* pumpkin_stem;
    static Block* melon_stem;
    static Block* vine;
    static Block* fence_gate;
    static Block* brick_stairs;
    static Block* stone_brick_stairs;
    static Block* mycelium;
    static Block* waterlily;
    static Block* nether_brick;
    static Block* nether_brick_fence;
    static Block* nether_brick_stairs;
    static Block* nether_wart;
    static Block* enchanting_table;
    static Block* brewing_stand;
    static Block* cauldron;
    static Block* end_portal;
    static Block* end_portal_frame;
    static Block* end_stone;
    static Block* dragon_egg;
    static Block* redstone_lamp;
    static Block* lit_redstone_lamp;
    static Block* double_wooden_slab;
    static Block* wooden_slab;
    static Block* cocoa;
    static Block* sandstone_stairs;
    static Block* emerald_ore;
    static Block* ender_chest;
    static Block* tripwire_hook;
    static Block* tripwire;
    static Block* emerald_block;
    static Block* spruce_stairs;
    static Block* birch_stairs;
    static Block* jungle_stairs;
    static Block* command_block;
    static Block* beacon;
    static Block* cobblestone_wall;
    static Block* flower_pot;
    static Block* carrots;
    static Block* potatoes;
    static Block* wooden_button;
    static Block* skull;
    static Block* anvil;
    static Block* trapped_chest;
    static Block* light_weighted_pressure_plate;
    static Block* heavy_weighted_pressure_plate;
    static Block* unpowered_comparator;
    static Block* powered_comparator;
    static Block* daylight_detector;
    static Block* redstone_block;
    static Block* quartz_ore;
    static Block* hopper;
    static Block* quartz_block;
    static Block* quartz_stairs;
    static Block* activator_rail;
    static Block* dropper;
    static Block* stained_hardened_clay;
    static Block* stained_glass_pane;
    static Block* leaves2;
    static Block* log2;
    static Block* acacia_stairs;
    static Block* dark_oak_stairs;
    static Block* slime;
    static Block* barrier;
    static Block* iron_trapdoor;
    static Block* prismarine;
    static Block* sea_lantern;
    static Block* hay_bale;
    static Block* carpet;
    static Block* hardened_clay;
    static Block* coal_block;
    static Block* packed_ice;
    static Block* double_plant;
    static Block* standing_banner;
    static Block* wall_banner;
    static Block* daylight_detector_inverted;
    static Block* red_sandstone;
    static Block* red_sandstone_stairs;
    static Block* double_stone_slab2;
    static Block* stone_slab2;
    static Block* spruce_fence_gate;
    static Block* birch_fence_gate;
    static Block* jungle_fence_gate;
    static Block* dark_oak_fence_gate;
    static Block* acacia_fence_gate;
    static Block* spruce_fence;
    static Block* birch_fence;
    static Block* jungle_fence;
    static Block* dark_oak_fence;
    static Block* acacia_fence;
    static Block* spruce_door;
    static Block* birch_door;
    static Block* jungle_door;
    static Block* acacia_door;
    static Block* dark_oak_door;

    static void registerBlock(ubyte_t, string_t, Block*);

    static void registerBlocks();

    static void deregisterBlocks();

    static Block *getBlock(ubyte_t);

    static Block *getBlock(string_t);

    static ubyte_t getBlockId(string_t);

    static string_t getBlockName(ubyte_t);

    /*

    A propos des constructeurs :
    Seul le constructeur Block(Material) est accepté.
    Cependant, étant donné que l'initialisation des blocks ne pourra se faire correctement
    que lorsque toutes les classes de Block auront été implémentées (ce qui va prendre du temps),
    je laisse ici ce constructeur Block(). Il devra être remplacé soit par Block(Material),
    soit par les constructeurs spécifiques des blocks qui ont une classe spécifique.
    Si vous ne comprenez pas, go sur le repo avec le code du NMS dans la classe Block.

    */
    Block();

    Block(Material*);

    AxisAlignedBB getBoundingBox();

    Material* getMaterial();

private:
    static std::unordered_map<ubyte_t, string_t> idToName;
    static std::unordered_map<ubyte_t, Block*> idToBlock;
    static std::unordered_map<string_t, ubyte_t> nameToId;
    static std::unordered_map<string_t, Block*> nameToBlock;

    AxisAlignedBB boundingBox;

    Material* blockMaterial;
};

#endif /* defined(__Serveur__Block__) */
