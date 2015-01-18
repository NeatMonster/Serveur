#include "Block.h"

void Block::registerBlock(ubyte_t id, string_t name, Block *block) {
    idToName.insert({id, name});
    idToBlock.insert({id, block});
    nameToId.insert({name, id,});
    nameToBlock.insert({name, block});
}

Block* Block::air = new Block();
Block* Block::stone = new Block();
Block* Block::grass = new Block();
Block* Block::dirt = new Block();
Block* Block::cobblestone = new Block();
Block* Block::planks = new Block();
Block* Block::sapling = new Block();
Block* Block::bedrock = new Block();
Block* Block::flowing_water = new Block();
Block* Block::water = new Block();
Block* Block::flowing_lava = new Block();
Block* Block::lava = new Block();
Block* Block::sand = new Block();
Block* Block::gravel = new Block();
Block* Block::gold_ore = new Block();
Block* Block::iron_ore = new Block();
Block* Block::coal_ore = new Block();
Block* Block::log = new Block();
Block* Block::leaves = new Block();
Block* Block::sponge = new Block();
Block* Block::glass = new Block();
Block* Block::lapis_ore = new Block();
Block* Block::lapis_block = new Block();
Block* Block::dispenser = new Block();
Block* Block::sandstone = new Block();
Block* Block::noteblock = new Block();
Block* Block::bed = new Block();
Block* Block::golden_rail = new Block();
Block* Block::detector_rail = new Block();
Block* Block::sticky_piston = new Block();
Block* Block::web = new Block();
Block* Block::tallgrass = new Block();
Block* Block::deadbush = new Block();
Block* Block::piston = new Block();
Block* Block::piston_head = new Block();
Block* Block::wool = new Block();
Block* Block::piston_extension = new Block();
Block* Block::yellow_flower = new Block();
Block* Block::red_flower = new Block();
Block* Block::brown_mushroom = new Block();
Block* Block::red_mushroom = new Block();
Block* Block::gold_block = new Block();
Block* Block::iron_block = new Block();
Block* Block::double_stone_slab = new Block();
Block* Block::stone_slab = new Block();

void Block::registerBlocks() {
    registerBlock(0, "air", air);
    registerBlock(1, "stone", stone);
    registerBlock(2, "grass", grass);
    registerBlock(3, "dirt", dirt);
    registerBlock(4, "cobblestone", cobblestone);
    registerBlock(5, "planks", planks);
    registerBlock(6, "sapling", sapling);
    registerBlock(7, "bedrock", bedrock);
    registerBlock(8, "flowing_water", flowing_water);
    registerBlock(9, "water", water);
    registerBlock(10, "flowing_lava", flowing_lava);
    registerBlock(11, "lava", lava);
    registerBlock(12, "sand", sand);
    registerBlock(13, "gravel", gravel);
    registerBlock(14, "gold_ore", gold_ore);
    registerBlock(15, "iron_ore", iron_ore);
    registerBlock(16, "coal_ore", coal_ore);
    registerBlock(17, "log", log);
    registerBlock(18, "leaves", leaves);
    registerBlock(19, "sponge", sponge);
    registerBlock(20, "glass", glass);
    registerBlock(21, "lapis_ore", lapis_ore);
    registerBlock(22, "lapis_block", lapis_block);
    registerBlock(23, "dispenser", dispenser);
    registerBlock(24, "sandstone", sandstone);
    registerBlock(25, "noteblock", noteblock);
    registerBlock(26, "bed", bed);
    registerBlock(27, "golden_rail", golden_rail);
    registerBlock(28, "detector_rail", detector_rail);
    registerBlock(29, "sticky_piston", sticky_piston);
    registerBlock(30, "web", web);
    registerBlock(31, "tallgrass", tallgrass);
    registerBlock(32, "deadbush", deadbush);
    registerBlock(33, "piston", piston);
    registerBlock(34, "piston_head", piston_head);
    registerBlock(35, "wool", wool);
    registerBlock(36, "piston_extension", piston_extension);
    registerBlock(37, "yellow_flower", yellow_flower);
    registerBlock(38, "red_flower", red_flower);
    registerBlock(39, "brown_mushroom", brown_mushroom);
    registerBlock(40, "red_mushroom", red_mushroom);
    registerBlock(41, "gold_block", gold_block);
    registerBlock(42, "iron_block", iron_block);
    registerBlock(43, "double_stone_slab", double_stone_slab);
    registerBlock(44, "stone_slab", stone_slab);
    registerBlock(45, "brick_block", new Block());
    registerBlock(46, "tnt", new Block());
    registerBlock(47, "bookshelf", new Block());
    registerBlock(48, "mossy_cobblestone", new Block());
    registerBlock(49, "obsidian", new Block());
    registerBlock(50, "torch", new Block());
    registerBlock(51, "fire", new Block());
    registerBlock(52, "mob_spawner", new Block());
    registerBlock(53, "oak_stairs", new Block());
    registerBlock(54, "chest", new Block());
    registerBlock(55, "redstone_wire", new Block());
    registerBlock(56, "diamond_ore", new Block());
    registerBlock(57, "diamond_block", new Block());
    registerBlock(58, "crafting_table", new Block());
    registerBlock(59, "wheat", new Block());
    registerBlock(60, "farmland", new Block());
    registerBlock(61, "furnace", new Block());
    registerBlock(62, "lit_furnace", new Block());
    registerBlock(63, "standing_sign", new Block());
    registerBlock(64, "wooden_door", new Block());
    registerBlock(65, "ladder", new Block());
    registerBlock(66, "rail", new Block());
    registerBlock(67, "stone_stairs", new Block());
    registerBlock(68, "wall_sign", new Block());
    registerBlock(69, "lever", new Block());
    registerBlock(70, "stone_pressure_plate", new Block());
    registerBlock(71, "iron_door", new Block());
    registerBlock(72, "wooden_pressure_plate", new Block());
    registerBlock(73, "redstone_ore", new Block());
    registerBlock(74, "lit_redstone_ore", new Block());
    registerBlock(75, "unlit_redstone_torch", new Block());
    registerBlock(76, "redstone_torch", new Block());
    registerBlock(77, "stone_button", new Block());
    registerBlock(78, "snow_layer", new Block());
    registerBlock(79, "ice", new Block());
    registerBlock(80, "snow", new Block());
    registerBlock(81, "cactus", new Block());
    registerBlock(82, "clay", new Block());
    registerBlock(83, "reeds", new Block());
    registerBlock(84, "jukebox", new Block());
    registerBlock(85, "fence", new Block());
    registerBlock(86, "pumpkin", new Block());
    registerBlock(87, "netherrack", new Block());
    registerBlock(88, "soul_sand", new Block());
    registerBlock(89, "glowstone", new Block());
    registerBlock(90, "portal", new Block());
    registerBlock(91, "lit_pumpkin", new Block());
    registerBlock(92, "cake", new Block());
    registerBlock(93, "unpowered_repeater", new Block());
    registerBlock(94, "powered_repeater", new Block());
    registerBlock(95, "stained_glass", new Block());
    registerBlock(96, "trapdoor", new Block());
    registerBlock(97, "monster_egg", new Block());
    registerBlock(98, "stonebrick", new Block());
    registerBlock(99, "brown_mushroom_block", new Block());
    registerBlock(100, "red_mushroom_block", new Block());
    registerBlock(101, "iron_bars", new Block());
    registerBlock(102, "glass_pane", new Block());
    registerBlock(103, "melon_block", new Block());
    registerBlock(104, "pumpkin_stem", new Block());
    registerBlock(105, "melon_stem", new Block());
    registerBlock(106, "vine", new Block());
    registerBlock(107, "fence_gate", new Block());
    registerBlock(108, "brick_stairs", new Block());
    registerBlock(109, "stone_brick_stairs", new Block());
    registerBlock(110, "mycelium", new Block());
    registerBlock(111, "waterlily", new Block());
    registerBlock(112, "nether_brick", new Block());
    registerBlock(113, "nether_brick_fence", new Block());
    registerBlock(114, "nether_brick_stairs", new Block());
    registerBlock(115, "nether_wart", new Block());
    registerBlock(116, "enchanting_table", new Block());
    registerBlock(117, "brewing_stand", new Block());
    registerBlock(118, "cauldron", new Block());
    registerBlock(119, "end_portal", new Block());
    registerBlock(120, "end_portal_frame", new Block());
    registerBlock(121, "end_stone", new Block());
    registerBlock(122, "dragon_egg", new Block());
    registerBlock(123, "redstone_lamp", new Block());
    registerBlock(124, "lit_redstone_lamp", new Block());
    registerBlock(125, "double_wooden_slab", new Block());
    registerBlock(126, "wooden_slab", new Block());
    registerBlock(127, "cocoa", new Block());
    registerBlock(128, "sandstone_stairs", new Block());
    registerBlock(129, "emerald_ore", new Block());
    registerBlock(130, "ender_chest", new Block());
    registerBlock(131, "tripwire_hook", new Block());
    registerBlock(132, "tripwire", new Block());
    registerBlock(133, "emerald_block", new Block());
    registerBlock(134, "spruce_stairs", new Block());
    registerBlock(135, "birch_stairs", new Block());
    registerBlock(136, "jungle_stairs", new Block());
    registerBlock(137, "command_block", new Block());
    registerBlock(138, "beacon", new Block());
    registerBlock(139, "cobblestone_wall", new Block());
    registerBlock(140, "flower_pot", new Block());
    registerBlock(141, "carrots", new Block());
    registerBlock(142, "potatoes", new Block());
    registerBlock(143, "wooden_button", new Block());
    registerBlock(144, "skull", new Block());
    registerBlock(145, "anvil", new Block());
    registerBlock(146, "trapped_chest", new Block());
    registerBlock(147, "light_weighted_pressure_plate", new Block());
    registerBlock(148, "heavy_weighted_pressure_plate", new Block());
    registerBlock(149, "unpowered_comparator", new Block());
    registerBlock(150, "powered_comparator", new Block());
    registerBlock(151, "daylight_detector", new Block());
    registerBlock(152, "redstone_block", new Block());
    registerBlock(153, "quartz_ore", new Block());
    registerBlock(154, "hopper", new Block());
    registerBlock(155, "quartz_block", new Block());
    registerBlock(156, "quartz_stairs", new Block());
    registerBlock(157, "activator_rail", new Block());
    registerBlock(158, "dropper", new Block());
    registerBlock(159, "stained_hardened_clay", new Block());
    registerBlock(160, "stained_glass_pane", new Block());
    registerBlock(161, "leaves2", new Block());
    registerBlock(162, "log2", new Block());
    registerBlock(163, "acacia_stairs", new Block());
    registerBlock(164, "dark_oak_stairs", new Block());
    registerBlock(165, "slime", new Block());
    registerBlock(166, "barrier", new Block());
    registerBlock(167, "iron_trapdoor", new Block());
    registerBlock(168, "prismarine", new Block());
    registerBlock(169, "sea_lantern", new Block());
    registerBlock(170, "hay_bale", new Block());
    registerBlock(171, "carpet", new Block());
    registerBlock(172, "hardened_clay", new Block());
    registerBlock(173, "coal_block", new Block());
    registerBlock(174, "packed_ice", new Block());
    registerBlock(175, "double_plant", new Block());
    registerBlock(176, "standing_banner", new Block());
    registerBlock(177, "wall_banner", new Block());
    registerBlock(178, "daylight_detector_inverted", new Block());
    registerBlock(179, "red_sandstone", new Block());
    registerBlock(180, "red_sandstone_stairs", new Block());
    registerBlock(181, "double_stone_slab2", new Block());
    registerBlock(182, "stone_slab2", new Block());
    registerBlock(183, "spruce_fence_gate", new Block());
    registerBlock(184, "birch_fence_gate", new Block());
    registerBlock(185, "jungle_fence_gate", new Block());
    registerBlock(186, "dark_oak_fence_gate", new Block());
    registerBlock(187, "acacia_fence_gate", new Block());
    registerBlock(188, "spruce_fence", new Block());
    registerBlock(189, "birch_fence", new Block());
    registerBlock(190, "jungle_fence", new Block());
    registerBlock(191, "dark_oak_fence", new Block());
    registerBlock(192, "acacia_fence", new Block());
    registerBlock(193, "spruce_door", new Block());
    registerBlock(194, "birch_door", new Block());
    registerBlock(195, "jungle_door", new Block());
    registerBlock(196, "acacia_door", new Block());
    registerBlock(197, "dark_oak_door", new Block());
}

void Block::deregisterBlocks() {
    std::unordered_map<string_t, Block*>::iterator it;

    for(it = nameToBlock.begin(); it != nameToBlock.end(); ++it)
        delete it->second;
}

Block *Block::getBlock(ubyte_t id) {
    return idToBlock[id];
}

Block *Block::getBlock(string_t name) {
    return nameToBlock[name];
}

ubyte_t Block::getBlockId(string_t name) {
    return nameToId[name];
}

string_t Block::getBlockName(ubyte_t id) {
    return idToName[id];
}

Block::Block() {}

std::unordered_map<ubyte_t, string_t> Block::idToName;
std::unordered_map<ubyte_t, Block*> Block::idToBlock;
std::unordered_map<string_t, ubyte_t> Block::nameToId;
std::unordered_map<string_t, Block*> Block::nameToBlock;
