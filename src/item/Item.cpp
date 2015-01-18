#include "Item.h"

#include "ItemPickaxe.h"

void Item::registerItem(ushort_t id, string_t name, Item *item) {
    idToName.insert({id, name});
    idToItem.insert({id, item});
    nameToId.insert({name, id,});
    nameToItem.insert({name, item});
}

void Item::registerItems() {
    registerItem(256, "iron_shovel", new Item());
    registerItem(257, "iron_pickaxe", new ItemPickaxe(ToolMaterial::IRON));
    registerItem(258, "iron_axe", new Item());
    registerItem(259, "flint_and_steel", new Item());
    registerItem(260, "apple", new Item());
    registerItem(261, "bow", new Item());
    registerItem(262, "arrow", new Item());
    registerItem(263, "coal", new Item());
    registerItem(264, "diamond", new Item());
    registerItem(265, "iron_ingot", new Item());
    registerItem(266, "gold_ingot", new Item());
    registerItem(267, "iron_sword", new Item());
    registerItem(268, "wooden_sword", new Item());
    registerItem(269, "wooden_shovel", new Item());
    registerItem(270, "wooden_pickaxe", new ItemPickaxe(ToolMaterial::WOOD));
    registerItem(271, "wooden_axe", new Item());
    registerItem(272, "stone_sword", new Item());
    registerItem(273, "stone_shovel", new Item());
    registerItem(274, "stone_pickaxe", new ItemPickaxe(ToolMaterial::STONE));
    registerItem(275, "stone_axe", new Item());
    registerItem(276, "diamond_sword", new Item());
    registerItem(277, "diamond_shovel", new Item());
    registerItem(278, "diamond_pickaxe", new ItemPickaxe(ToolMaterial::EMERALD));
    registerItem(279, "diamond_axe", new Item());
    registerItem(280, "stick", new Item());
    registerItem(281, "bowl", new Item());
    registerItem(282, "mushroom_stew", new Item());
    registerItem(283, "golden_sword", new Item());
    registerItem(284, "golden_shovel", new Item());
    registerItem(285, "golden_pickaxe", new ItemPickaxe(ToolMaterial::GOLD));
    registerItem(286, "golden_axe", new Item());
    registerItem(287, "string", new Item());
    registerItem(288, "feather", new Item());
    registerItem(289, "gunpowder", new Item());
    registerItem(290, "wooden_hoe", new Item());
    registerItem(291, "stone_hoe", new Item());
    registerItem(292, "iron_hoe", new Item());
    registerItem(293, "diamond_hoe", new Item());
    registerItem(294, "golden_hoe", new Item());
    registerItem(295, "wheat_seeds", new Item());
    registerItem(296, "wheat", new Item());
    registerItem(297, "bread", new Item());
    registerItem(298, "leather_helmet", new Item());
    registerItem(299, "leather_chestplate", new Item());
    registerItem(300, "leather_leggings", new Item());
    registerItem(301, "leather_boots", new Item());
    registerItem(302, "chainmail_helmet", new Item());
    registerItem(303, "chainmail_chestplate", new Item());
    registerItem(304, "chainmail_leggings", new Item());
    registerItem(305, "chainmail_boots", new Item());
    registerItem(306, "iron_helmet", new Item());
    registerItem(307, "iron_chestplate", new Item());
    registerItem(308, "iron_leggings", new Item());
    registerItem(309, "iron_boots", new Item());
    registerItem(310, "diamond_helmet", new Item());
    registerItem(311, "diamond_chestplate", new Item());
    registerItem(312, "diamond_leggings", new Item());
    registerItem(313, "diamond_boots", new Item());
    registerItem(314, "golden_helmet", new Item());
    registerItem(315, "golden_chestplate", new Item());
    registerItem(316, "golden_leggings", new Item());
    registerItem(317, "golden_boots", new Item());
    registerItem(318, "flint", new Item());
    registerItem(319, "porkchop", new Item());
    registerItem(320, "cooked_porkchop", new Item());
    registerItem(321, "painting", new Item());
    registerItem(322, "golden_apple", new Item());
    registerItem(323, "sign", new Item());
    registerItem(324, "wooden_door", new Item());
    registerItem(325, "bucket", new Item());
    registerItem(326, "water_bucket", new Item());
    registerItem(327, "lava_bucket", new Item());
    registerItem(328, "minecart", new Item());
    registerItem(329, "saddle", new Item());
    registerItem(330, "iron_door", new Item());
    registerItem(331, "redstone", new Item());
    registerItem(332, "snowball", new Item());
    registerItem(333, "boat", new Item());
    registerItem(334, "leather", new Item());
    registerItem(335, "milk_bucket", new Item());
    registerItem(336, "brick", new Item());
    registerItem(337, "clay_ball", new Item());
    registerItem(338, "reeds", new Item());
    registerItem(339, "paper", new Item());
    registerItem(340, "book", new Item());
    registerItem(341, "slime_ball", new Item());
    registerItem(342, "chest_minecart", new Item());
    registerItem(343, "furnace_minecart", new Item());
    registerItem(344, "egg", new Item());
    registerItem(345, "compass", new Item());
    registerItem(346, "fishing_rod", new Item());
    registerItem(347, "clock", new Item());
    registerItem(348, "glowstone_dust", new Item());
    registerItem(349, "fish", new Item());
    registerItem(350, "cooked_fish", new Item());
    registerItem(351, "dye", new Item());
    registerItem(352, "bone", new Item());
    registerItem(353, "sugar", new Item());
    registerItem(354, "cake", new Item());
    registerItem(355, "bed", new Item());
    registerItem(356, "repeater", new Item());
    registerItem(357, "cookie", new Item());
    registerItem(358, "filled_map", new Item());
    registerItem(359, "shears", new Item());
    registerItem(360, "melon", new Item());
    registerItem(361, "pumpkin_seeds", new Item());
    registerItem(362, "melon_seeds", new Item());
    registerItem(363, "beef", new Item());
    registerItem(364, "cooked_beef", new Item());
    registerItem(365, "chicken", new Item());
    registerItem(366, "cooked_chicken", new Item());
    registerItem(367, "rotten_flesh", new Item());
    registerItem(368, "ender_pearl", new Item());
    registerItem(369, "blaze_rod", new Item());
    registerItem(370, "ghast_tear", new Item());
    registerItem(371, "gold_nugget", new Item());
    registerItem(372, "nether_wart", new Item());
    registerItem(373, "potion", new Item());
    registerItem(374, "glass_bottle", new Item());
    registerItem(375, "spider_eye", new Item());
    registerItem(376, "fermented_spider_eye", new Item());
    registerItem(377, "blaze_powder", new Item());
    registerItem(378, "magma_cream", new Item());
    registerItem(379, "brewing_stand", new Item());
    registerItem(380, "cauldron", new Item());
    registerItem(381, "ender_eye", new Item());
    registerItem(382, "speckled_melon", new Item());
    registerItem(383, "spawn_egg", new Item());
    registerItem(384, "experience_bottle", new Item());
    registerItem(385, "fire_charge", new Item());
    registerItem(386, "writable_book", new Item());
    registerItem(387, "written_book", new Item());
    registerItem(388, "emerald", new Item());
    registerItem(389, "item_frame", new Item());
    registerItem(390, "flower_pot", new Item());
    registerItem(391, "carrot", new Item());
    registerItem(392, "potato", new Item());
    registerItem(393, "baked_potato", new Item());
    registerItem(394, "poisonous_potato", new Item());
    registerItem(395, "map", new Item());
    registerItem(396, "golden_carrot", new Item());
    registerItem(397, "skull", new Item());
    registerItem(398, "carrot_on_a_stick", new Item());
    registerItem(399, "nether_star", new Item());
    registerItem(400, "pumpkin_pie", new Item());
    registerItem(401, "fireworks", new Item());
    registerItem(402, "firework_charge", new Item());
    registerItem(403, "enchanted_book", new Item());
    registerItem(404, "comparator", new Item());
    registerItem(405, "netherbrick", new Item());
    registerItem(406, "quartz", new Item());
    registerItem(407, "tnt_minecart", new Item());
    registerItem(408, "hopper_minecart", new Item());
    registerItem(409, "prismarine_shard", new Item());
    registerItem(410, "prismarine_crystals", new Item());
    registerItem(411, "rabbit", new Item());
    registerItem(412, "cooked_rabbit", new Item());
    registerItem(413, "rabbit_stew", new Item());
    registerItem(414, "rabbit_foot", new Item());
    registerItem(415, "rabbit_hide", new Item());
    registerItem(416, "armor_stand", new Item());
    registerItem(417, "iron_horse_armor", new Item());
    registerItem(418, "golden_horse_armor", new Item());
    registerItem(419, "diamond_horse_armor", new Item());
    registerItem(420, "lead", new Item());
    registerItem(421, "name_tag", new Item());
    registerItem(422, "command_block_minecart", new Item());
    registerItem(423, "mutton", new Item());
    registerItem(424, "cooked_mutton", new Item());
    registerItem(425, "banner", new Item());
    registerItem(427, "spruce_door", new Item());
    registerItem(428, "birch_door", new Item());
    registerItem(429, "jungle_door", new Item());
    registerItem(430, "acacia_door", new Item());
    registerItem(431, "dark_oak_door", new Item());
    registerItem(2256, "record_13", new Item());
    registerItem(2257, "record_cat", new Item());
    registerItem(2258, "record_blocks", new Item());
    registerItem(2259, "record_chirp", new Item());
    registerItem(2260, "record_far", new Item());
    registerItem(2261, "record_mall", new Item());
    registerItem(2262, "record_mellohi", new Item());
    registerItem(2263, "record_stal", new Item());
    registerItem(2264, "record_strad", new Item());
    registerItem(2265, "record_ward", new Item());
    registerItem(2266, "record_11", new Item());
    registerItem(2267, "record_wait", new Item());
}

void Item::deRegisterItems() {
    std::unordered_map<string_t, Item*>::iterator it;

    for(it = nameToItem.begin(); it != nameToItem.end(); ++it)
        delete it->second;
}

Item *Item::getItem(ubyte_t id) {
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

std::unordered_map<ushort_t, string_t> Item::idToName;
std::unordered_map<ushort_t, Item*> Item::idToItem;
std::unordered_map<string_t, ushort_t> Item::nameToId;
std::unordered_map<string_t, Item*> Item::nameToItem;
