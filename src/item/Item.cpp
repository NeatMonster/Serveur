#include "Item.h"

#include "ItemAxe.h"
#include "ItemHoe.h"
#include "ItemPickaxe.h"
#include "ItemSpade.h"

Item* Item::iron_shovel;
Item* Item::iron_pickaxe;
Item* Item::iron_axe;
Item* Item::flint_and_steel;
Item* Item::apple;
Item* Item::bow;
Item* Item::arrow;
Item* Item::coal;
Item* Item::diamond;
Item* Item::iron_ingot;
Item* Item::gold_ingot;
Item* Item::iron_sword;
Item* Item::wooden_sword;
Item* Item::wooden_shovel;
Item* Item::wooden_pickaxe;
Item* Item::wooden_axe;
Item* Item::stone_sword;
Item* Item::stone_shovel;
Item* Item::stone_pickaxe;
Item* Item::stone_axe;
Item* Item::diamond_sword;
Item* Item::diamond_shovel;
Item* Item::diamond_pickaxe;
Item* Item::diamond_axe;
Item* Item::stick;
Item* Item::bowl;
Item* Item::mushroom_stew;
Item* Item::golden_sword;
Item* Item::golden_shovel;
Item* Item::golden_pickaxe;
Item* Item::golden_axe;
Item* Item::string;
Item* Item::feather;
Item* Item::gunpowder;
Item* Item::wooden_hoe;
Item* Item::stone_hoe;
Item* Item::iron_hoe;
Item* Item::diamond_hoe;
Item* Item::golden_hoe;
Item* Item::wheat_seeds;
Item* Item::wheat;
Item* Item::bread;
Item* Item::leather_helmet;
Item* Item::leather_chestplate;
Item* Item::leather_leggings;
Item* Item::leather_boots;
Item* Item::chainmail_helmet;
Item* Item::chainmail_chestplate;
Item* Item::chainmail_leggings;
Item* Item::chainmail_boots;
Item* Item::iron_helmet;
Item* Item::iron_chestplate;
Item* Item::iron_leggings;
Item* Item::iron_boots;
Item* Item::diamond_helmet;
Item* Item::diamond_chestplate;
Item* Item::diamond_leggings;
Item* Item::diamond_boots;
Item* Item::golden_helmet;
Item* Item::golden_chestplate;
Item* Item::golden_leggings;
Item* Item::golden_boots;
Item* Item::flint;
Item* Item::porkchop;
Item* Item::cooked_porkchop;
Item* Item::painting;
Item* Item::golden_apple;
Item* Item::sign;
Item* Item::wooden_door;
Item* Item::bucket;
Item* Item::water_bucket;
Item* Item::lava_bucket;
Item* Item::minecart;
Item* Item::saddle;
Item* Item::iron_door;
Item* Item::redstone;
Item* Item::snowball;
Item* Item::boat;
Item* Item::leather;
Item* Item::milk_bucket;
Item* Item::brick;
Item* Item::clay_ball;
Item* Item::reeds;
Item* Item::paper;
Item* Item::book;
Item* Item::slime_ball;
Item* Item::chest_minecart;
Item* Item::furnace_minecart;
Item* Item::egg;
Item* Item::compass;
Item* Item::fishing_rod;
Item* Item::clock;
Item* Item::glowstone_dust;
Item* Item::fish;
Item* Item::cooked_fish;
Item* Item::dye;
Item* Item::bone;
Item* Item::sugar;
Item* Item::cake;
Item* Item::bed;
Item* Item::repeater;
Item* Item::cookie;
Item* Item::filled_map;
Item* Item::shears;
Item* Item::melon;
Item* Item::pumpkin_seeds;
Item* Item::melon_seeds;
Item* Item::beef;
Item* Item::cooked_beef;
Item* Item::chicken;
Item* Item::cooked_chicken;
Item* Item::rotten_flesh;
Item* Item::ender_pearl;
Item* Item::blaze_rod;
Item* Item::ghast_tear;
Item* Item::gold_nugget;
Item* Item::nether_wart;
Item* Item::potion;
Item* Item::glass_bottle;
Item* Item::spider_eye;
Item* Item::fermented_spider_eye;
Item* Item::blaze_powder;
Item* Item::magma_cream;
Item* Item::brewing_stand;
Item* Item::cauldron;
Item* Item::ender_eye;
Item* Item::speckled_melon;
Item* Item::spawn_egg;
Item* Item::experience_bottle;
Item* Item::fire_charge;
Item* Item::writable_book;
Item* Item::written_book;
Item* Item::emerald;
Item* Item::item_frame;
Item* Item::flower_pot;
Item* Item::carrot;
Item* Item::potato;
Item* Item::baked_potato;
Item* Item::poisonous_potato;
Item* Item::map;
Item* Item::golden_carrot;
Item* Item::skull;
Item* Item::carrot_on_a_stick;
Item* Item::nether_star;
Item* Item::pumpkin_pie;
Item* Item::fireworks;
Item* Item::firework_charge;
Item* Item::enchanted_book;
Item* Item::comparator;
Item* Item::netherbrick;
Item* Item::quartz;
Item* Item::tnt_minecart;
Item* Item::hopper_minecart;
Item* Item::prismarine_shard;
Item* Item::prismarine_crystals;
Item* Item::rabbit;
Item* Item::cooked_rabbit;
Item* Item::rabbit_stew;
Item* Item::rabbit_foot;
Item* Item::rabbit_hide;
Item* Item::armor_stand;
Item* Item::iron_horse_armor;
Item* Item::golden_horse_armor;
Item* Item::diamond_horse_armor;
Item* Item::lead;
Item* Item::name_tag;
Item* Item::command_block_minecart;
Item* Item::mutton;
Item* Item::cooked_mutton;
Item* Item::banner;
Item* Item::spruce_door;
Item* Item::birch_door;
Item* Item::jungle_door;
Item* Item::acacia_door;
Item* Item::dark_oak_door;
Item* Item::record_13;
Item* Item::record_cat;
Item* Item::record_blocks;
Item* Item::record_chirp;
Item* Item::record_far;
Item* Item::record_mall;
Item* Item::record_mellohi;
Item* Item::record_stal;
Item* Item::record_strad;
Item* Item::record_ward;
Item* Item::record_11;
Item* Item::record_wait;

void Item::registerItem(ushort_t id, string_t name, Item *item) {
    idToName[id] = name;
    idToItem[id] = item;
    nameToId[name] = id;
    nameToItem[name] = item;
}

void Item::registerItems() {
    // TODO Ajouter les items correspondants aux blocs
    registerItem(256, "iron_shovel", iron_shovel = new ItemSpade(ItemTool::ToolMaterial::IRON));
    registerItem(257, "iron_pickaxe", iron_pickaxe = new ItemPickaxe(ItemTool::ToolMaterial::IRON));
    registerItem(258, "iron_axe", iron_axe = new ItemAxe(ItemTool::ToolMaterial::IRON));
    registerItem(259, "flint_and_steel", flint_and_steel = new Item());
    registerItem(260, "apple", apple = new Item());
    registerItem(261, "bow", bow = new Item());
    registerItem(262, "arrow", (arrow = new Item())->setCreativeTab(CreativeTabs::tabCombat));
    registerItem(263, "coal", coal = new Item());
    registerItem(264, "diamond", (diamond = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(265, "iron_ingot", (iron_ingot = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(266, "gold_ingot", (gold_ingot = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(267, "iron_sword", iron_sword = new Item());
    registerItem(268, "wooden_sword", wooden_sword = new Item());
    registerItem(269, "wooden_shovel", wooden_shovel = new ItemSpade(ItemTool::ToolMaterial::WOOD));
    registerItem(270, "wooden_pickaxe", wooden_pickaxe = new ItemPickaxe(ItemTool::ToolMaterial::WOOD));
    registerItem(271, "wooden_axe", wooden_axe = new ItemAxe(ItemTool::ToolMaterial::WOOD));
    registerItem(272, "stone_sword", stone_sword = new Item());
    registerItem(273, "stone_shovel", stone_shovel = new ItemSpade(ItemTool::ToolMaterial::STONE));
    registerItem(274, "stone_pickaxe", stone_pickaxe = new ItemPickaxe(ItemTool::ToolMaterial::STONE));
    registerItem(275, "stone_axe", stone_axe = new ItemAxe(ItemTool::ToolMaterial::STONE));
    registerItem(276, "diamond_sword", diamond_sword = new Item());
    registerItem(277, "diamond_shovel", diamond_shovel = new ItemSpade(ItemTool::ToolMaterial::DIAMOND));
    registerItem(278, "diamond_pickaxe", diamond_pickaxe = new ItemPickaxe(ItemTool::ToolMaterial::DIAMOND));
    registerItem(279, "diamond_axe", diamond_axe = new ItemAxe(ItemTool::ToolMaterial::DIAMOND));
    registerItem(280, "stick", (stick = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(281, "bowl", (bowl = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(282, "mushroom_stew", mushroom_stew = new Item());
    registerItem(283, "golden_sword", golden_sword = new Item());
    registerItem(284, "golden_shovel", golden_shovel = new ItemSpade(ItemTool::ToolMaterial::GOLD));
    registerItem(285, "golden_pickaxe", golden_pickaxe = new ItemPickaxe(ItemTool::ToolMaterial::GOLD));
    registerItem(286, "golden_axe", golden_axe = new ItemAxe(ItemTool::ToolMaterial::GOLD));
    registerItem(287, "string", (string = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(288, "feather", (feather = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(289, "gunpowder", (gunpowder = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(290, "wooden_hoe", wooden_hoe = new ItemHoe(ItemTool::ToolMaterial::WOOD));
    registerItem(291, "stone_hoe", stone_hoe = new ItemHoe(ItemTool::ToolMaterial::STONE));
    registerItem(292, "iron_hoe", iron_hoe = new ItemHoe(ItemTool::ToolMaterial::IRON));
    registerItem(293, "diamond_hoe", diamond_hoe = new ItemHoe(ItemTool::ToolMaterial::DIAMOND));
    registerItem(294, "golden_hoe", golden_hoe = new ItemHoe(ItemTool::ToolMaterial::GOLD));
    registerItem(295, "wheat_seeds", wheat_seeds = new Item());
    registerItem(296, "wheat", (wheat = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(297, "bread", bread = new Item());
    registerItem(298, "leather_helmet", leather_helmet = new Item());
    registerItem(299, "leather_chestplate", leather_chestplate = new Item());
    registerItem(300, "leather_leggings", leather_leggings = new Item());
    registerItem(301, "leather_boots", leather_boots = new Item());
    registerItem(302, "chainmail_helmet", chainmail_helmet = new Item());
    registerItem(303, "chainmail_chestplate", chainmail_chestplate = new Item());
    registerItem(304, "chainmail_leggings", chainmail_leggings = new Item());
    registerItem(305, "chainmail_boots", chainmail_boots = new Item());
    registerItem(306, "iron_helmet", iron_helmet = new Item());
    registerItem(307, "iron_chestplate", iron_chestplate = new Item());
    registerItem(308, "iron_leggings", iron_leggings = new Item());
    registerItem(309, "iron_boots", iron_boots = new Item());
    registerItem(310, "diamond_helmet", diamond_helmet = new Item());
    registerItem(311, "diamond_chestplate", diamond_chestplate = new Item());
    registerItem(312, "diamond_leggings", diamond_leggings = new Item());
    registerItem(313, "diamond_boots", diamond_boots = new Item());
    registerItem(314, "golden_helmet", golden_helmet = new Item());
    registerItem(315, "golden_chestplate", golden_chestplate = new Item());
    registerItem(316, "golden_leggings", golden_leggings = new Item());
    registerItem(317, "golden_boots", golden_boots = new Item());
    registerItem(318, "flint", (flint = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(319, "porkchop", porkchop = new Item());
    registerItem(320, "cooked_porkchop", cooked_porkchop = new Item());
    registerItem(321, "painting", painting = new Item());
    registerItem(322, "golden_apple", golden_apple = new Item());
    registerItem(323, "sign", sign = new Item());
    registerItem(324, "wooden_door", wooden_door = new Item());
    registerItem(325, "bucket", bucket = new Item());
    registerItem(326, "water_bucket", water_bucket = new Item());
    registerItem(327, "lava_bucket", lava_bucket = new Item());
    registerItem(328, "minecart", minecart = new Item());
    registerItem(329, "saddle", saddle = new Item());
    registerItem(330, "iron_door", iron_door = new Item());
    registerItem(331, "redstone", redstone = new Item());
    registerItem(332, "snowball", snowball = new Item());
    registerItem(333, "boat", boat = new Item());
    registerItem(334, "leather", (leather = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(335, "milk_bucket", milk_bucket = new Item());
    registerItem(336, "brick", (brick = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(337, "clay_ball", (clay_ball = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(338, "reeds", (reeds = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(339, "paper", (paper = new Item())->setCreativeTab(CreativeTabs::tabMisc));
    registerItem(340, "book", (book = new Item())->setCreativeTab(CreativeTabs::tabMisc));
    registerItem(341, "slime_ball", (slime_ball = new Item())->setCreativeTab(CreativeTabs::tabMisc));
    registerItem(342, "chest_minecart", chest_minecart = new Item());
    registerItem(343, "furnace_minecart", furnace_minecart = new Item());
    registerItem(344, "egg", egg = new Item());
    registerItem(345, "compass", (compass = new Item())->setCreativeTab(CreativeTabs::tabTools));
    registerItem(346, "fishing_rod", fishing_rod = new Item());
    registerItem(347, "clock", (clock = new Item())->setCreativeTab(CreativeTabs::tabTools));
    registerItem(348, "glowstone_dust", (glowstone_dust = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(349, "fish", fish = new Item());
    registerItem(350, "cooked_fish", cooked_fish = new Item());
    registerItem(351, "dye", dye = new Item());
    registerItem(352, "bone", (bone = new Item())->setCreativeTab(CreativeTabs::tabMisc));
    registerItem(353, "sugar", (sugar = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(354, "cake", (cake = new Item())->setCreativeTab(CreativeTabs::tabFood));
    registerItem(355, "bed", bed = new Item());
    registerItem(356, "repeater", (repeater = new Item())->setCreativeTab(CreativeTabs::tabRedstone));
    registerItem(357, "cookie", cookie = new Item());
    registerItem(358, "filled_map", filled_map = new Item());
    registerItem(359, "shears", shears = new Item());
    registerItem(360, "melon", melon = new Item());
    registerItem(361, "pumpkin_seeds", pumpkin_seeds = new Item());
    registerItem(362, "melon_seeds", melon_seeds = new Item());
    registerItem(363, "beef", beef = new Item());
    registerItem(364, "cooked_beef", cooked_beef = new Item());
    registerItem(365, "chicken", chicken = new Item());
    registerItem(366, "cooked_chicken", cooked_chicken = new Item());
    registerItem(367, "rotten_flesh", rotten_flesh = new Item());
    registerItem(368, "ender_pearl", ender_pearl = new Item());
    registerItem(369, "blaze_rod", (blaze_rod = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(370, "ghast_tear", (ghast_tear = new Item())->setCreativeTab(CreativeTabs::tabBrewing));
    registerItem(371, "gold_nugget", (gold_nugget = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(372, "nether_wart", nether_wart = new Item());
    registerItem(373, "potion", potion = new Item());
    registerItem(374, "glass_bottle", glass_bottle = new Item());
    registerItem(375, "spider_eye", spider_eye = new Item());
    registerItem(376, "fermented_spider_eye", (fermented_spider_eye = new Item())->setCreativeTab(CreativeTabs::tabBrewing));
    registerItem(377, "blaze_powder", (blaze_powder = new Item())->setCreativeTab(CreativeTabs::tabBrewing));
    registerItem(378, "magma_cream", (magma_cream = new Item())->setCreativeTab(CreativeTabs::tabBrewing));
    registerItem(379, "brewing_stand", (brewing_stand = new Item())->setCreativeTab(CreativeTabs::tabBrewing));
    registerItem(380, "cauldron", (cauldron = new Item())->setCreativeTab(CreativeTabs::tabBrewing));
    registerItem(381, "ender_eye", ender_eye = new Item());
    registerItem(382, "speckled_melon", (speckled_melon = new Item())->setCreativeTab(CreativeTabs::tabBrewing));
    registerItem(383, "spawn_egg", spawn_egg = new Item());
    registerItem(384, "experience_bottle", experience_bottle = new Item());
    registerItem(385, "fire_charge", fire_charge = new Item());
    registerItem(386, "writable_book", (writable_book = new Item())->setCreativeTab(CreativeTabs::tabMisc));
    registerItem(387, "written_book", written_book = new Item());
    registerItem(388, "emerald", emerald = (new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(389, "item_frame", item_frame = new Item());
    registerItem(390, "flower_pot", (flower_pot = new Item())->setCreativeTab(CreativeTabs::tabDecorations));
    registerItem(391, "carrot", carrot = new Item());
    registerItem(392, "potato", potato = new Item());
    registerItem(393, "baked_potato", baked_potato = new Item());
    registerItem(394, "poisonous_potato", poisonous_potato = new Item());
    registerItem(395, "map", map = new Item());
    registerItem(396, "golden_carrot", (golden_carrot = new Item())->setCreativeTab(CreativeTabs::tabBrewing));
    registerItem(397, "skull", skull = new Item());
    registerItem(398, "carrot_on_a_stick", carrot_on_a_stick = new Item());
    registerItem(399, "nether_star", (nether_star = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(400, "pumpkin_pie", (pumpkin_pie = new Item())->setCreativeTab(CreativeTabs::tabFood));
    registerItem(401, "fireworks", fireworks = new Item());
    registerItem(402, "firework_charge", (firework_charge = new Item())->setCreativeTab(CreativeTabs::tabMisc));
    registerItem(403, "enchanted_book", enchanted_book = new Item());
    registerItem(404, "comparator", (comparator = new Item())->setCreativeTab(CreativeTabs::tabRedstone));
    registerItem(405, "netherbrick", (netherbrick = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(406, "quartz", (quartz = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(407, "tnt_minecart", tnt_minecart = new Item());
    registerItem(408, "hopper_minecart", hopper_minecart = new Item());
    registerItem(409, "prismarine_shard", (prismarine_shard = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(410, "prismarine_crystals", (prismarine_crystals = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(411, "rabbit", rabbit = new Item());
    registerItem(412, "cooked_rabbit", cooked_rabbit = new Item());
    registerItem(413, "rabbit_stew", rabbit_stew = new Item());
    registerItem(414, "rabbit_foot", (rabbit_foot = new Item())->setCreativeTab(CreativeTabs::tabBrewing));
    registerItem(415, "rabbit_hide", (rabbit_hide = new Item())->setCreativeTab(CreativeTabs::tabMaterials));
    registerItem(416, "armor_stand", armor_stand = new Item());
    registerItem(417, "iron_horse_armor", (iron_horse_armor = new Item())->setCreativeTab(CreativeTabs::tabMisc));
    registerItem(418, "golden_horse_armor", (golden_horse_armor = new Item())->setCreativeTab(CreativeTabs::tabMisc));
    registerItem(419, "diamond_horse_armor", (diamond_horse_armor = new Item())->setCreativeTab(CreativeTabs::tabMisc));
    registerItem(420, "lead", lead = new Item());
    registerItem(421, "name_tag", name_tag = new Item());
    registerItem(422, "command_block_minecart", command_block_minecart = new Item());
    registerItem(423, "mutton", mutton = new Item());
    registerItem(424, "cooked_mutton", cooked_mutton = new Item());
    registerItem(425, "banner", banner = new Item());
    registerItem(427, "spruce_door", spruce_door = new Item());
    registerItem(428, "birch_door", birch_door = new Item());
    registerItem(429, "jungle_door", jungle_door = new Item());
    registerItem(430, "acacia_door", acacia_door = new Item());
    registerItem(431, "dark_oak_door", dark_oak_door = new Item());
    registerItem(2256, "record_13", record_13 = new Item());
    registerItem(2257, "record_cat", record_cat = new Item());
    registerItem(2258, "record_blocks", record_blocks = new Item());
    registerItem(2259, "record_chirp", record_chirp = new Item());
    registerItem(2260, "record_far", record_far = new Item());
    registerItem(2261, "record_mall", record_mall = new Item());
    registerItem(2262, "record_mellohi", record_mellohi = new Item());
    registerItem(2263, "record_stal", record_stal = new Item());
    registerItem(2264, "record_strad", record_strad = new Item());
    registerItem(2265, "record_ward", record_ward = new Item());
    registerItem(2266, "record_11", record_11 = new Item());
    registerItem(2267, "record_wait", record_wait = new Item());
}

void Item::deregisterItems() {
    std::unordered_map<string_t, Item*>::iterator it;

    for(it = nameToItem.begin(); it != nameToItem.end(); ++it)
        delete it->second;
}

Item *Item::getItem(ushort_t id) {
    return idToItem[id];
}

Item *Item::getItem(string_t name) {
    return nameToItem[name];
}

ushort_t Item::getItemId(string_t name) {
    return nameToId[name];
}

string_t Item::getItemName(ushort_t id) {
    return idToName[id];
}

Item::Item() {}

int_t Item::getMaxDamage() {
    return maxDamage;
}

int_t Item::getMaxStackSize() {
    return maxStackSize;
}

Item* Item::setMaxDamage(int_t maxDurability) {
    maxDamage = maxDurability;
    return this;
}

Item* Item::setCreativeTab(CreativeTabs* tab) {
    tabToDisplayOn = tab;
    return this;
}

std::unordered_map<ushort_t, string_t> Item::idToName;
std::unordered_map<ushort_t, Item*> Item::idToItem;
std::unordered_map<string_t, ushort_t> Item::nameToId;
std::unordered_map<string_t, Item*> Item::nameToItem;
