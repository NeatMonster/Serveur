#ifndef __Serveur__Item__
#define __Serveur__Item__

#include "Types.h"

#include <unordered_map>

class Block;
class EntityPlayer;
class ItemStack;

class Item {
public:
    static Item* iron_shovel;
    static Item* iron_pickaxe;
    static Item* iron_axe;
    static Item* flint_and_steel;
    static Item* apple;
    static Item* bow;
    static Item* arrow;
    static Item* coal;
    static Item* diamond;
    static Item* iron_ingot;
    static Item* gold_ingot;
    static Item* iron_sword;
    static Item* wooden_sword;
    static Item* wooden_shovel;
    static Item* wooden_pickaxe;
    static Item* wooden_axe;
    static Item* stone_sword;
    static Item* stone_shovel;
    static Item* stone_pickaxe;
    static Item* stone_axe;
    static Item* diamond_sword;
    static Item* diamond_shovel;
    static Item* diamond_pickaxe;
    static Item* diamond_axe;
    static Item* stick;
    static Item* bowl;
    static Item* mushroom_stew;
    static Item* golden_sword;
    static Item* golden_shovel;
    static Item* golden_pickaxe;
    static Item* golden_axe;
    static Item* string;
    static Item* feather;
    static Item* gunpowder;
    static Item* wooden_hoe;
    static Item* stone_hoe;
    static Item* iron_hoe;
    static Item* diamond_hoe;
    static Item* golden_hoe;
    static Item* wheat_seeds;
    static Item* wheat;
    static Item* bread;
    static Item* leather_helmet;
    static Item* leather_chestplate;
    static Item* leather_leggings;
    static Item* leather_boots;
    static Item* chainmail_helmet;
    static Item* chainmail_chestplate;
    static Item* chainmail_leggings;
    static Item* chainmail_boots;
    static Item* iron_helmet;
    static Item* iron_chestplate;
    static Item* iron_leggings;
    static Item* iron_boots;
    static Item* diamond_helmet;
    static Item* diamond_chestplate;
    static Item* diamond_leggings;
    static Item* diamond_boots;
    static Item* golden_helmet;
    static Item* golden_chestplate;
    static Item* golden_leggings;
    static Item* golden_boots;
    static Item* flint;
    static Item* porkchop;
    static Item* cooked_porkchop;
    static Item* painting;
    static Item* golden_apple;
    static Item* sign;
    static Item* wooden_door;
    static Item* bucket;
    static Item* water_bucket;
    static Item* lava_bucket;
    static Item* minecart;
    static Item* saddle;
    static Item* iron_door;
    static Item* redstone;
    static Item* snowball;
    static Item* boat;
    static Item* leather;
    static Item* milk_bucket;
    static Item* brick;
    static Item* clay_ball;
    static Item* reeds;
    static Item* paper;
    static Item* book;
    static Item* slime_ball;
    static Item* chest_minecart;
    static Item* furnace_minecart;
    static Item* egg;
    static Item* compass;
    static Item* fishing_rod;
    static Item* clock;
    static Item* glowstone_dust;
    static Item* fish;
    static Item* cooked_fish;
    static Item* dye;
    static Item* bone;
    static Item* sugar;
    static Item* cake;
    static Item* bed;
    static Item* repeater;
    static Item* cookie;
    static Item* filled_map;
    static Item* shears;
    static Item* melon;
    static Item* pumpkin_seeds;
    static Item* melon_seeds;
    static Item* beef;
    static Item* cooked_beef;
    static Item* chicken;
    static Item* cooked_chicken;
    static Item* rotten_flesh;
    static Item* ender_pearl;
    static Item* blaze_rod;
    static Item* ghast_tear;
    static Item* gold_nugget;
    static Item* nether_wart;
    static Item* potion;
    static Item* glass_bottle;
    static Item* spider_eye;
    static Item* fermented_spider_eye;
    static Item* blaze_powder;
    static Item* magma_cream;
    static Item* brewing_stand;
    static Item* cauldron;
    static Item* ender_eye;
    static Item* speckled_melon;
    static Item* spawn_egg;
    static Item* experience_bottle;
    static Item* fire_charge;
    static Item* writable_book;
    static Item* written_book;
    static Item* emerald;
    static Item* item_frame;
    static Item* flower_pot;
    static Item* carrot;
    static Item* potato;
    static Item* baked_potato;
    static Item* poisonous_potato;
    static Item* map;
    static Item* golden_carrot;
    static Item* skull;
    static Item* carrot_on_a_stick;
    static Item* nether_star;
    static Item* pumpkin_pie;
    static Item* fireworks;
    static Item* firework_charge;
    static Item* enchanted_book;
    static Item* comparator;
    static Item* netherbrick;
    static Item* quartz;
    static Item* tnt_minecart;
    static Item* hopper_minecart;
    static Item* prismarine_shard;
    static Item* prismarine_crystals;
    static Item* rabbit;
    static Item* cooked_rabbit;
    static Item* rabbit_stew;
    static Item* rabbit_foot;
    static Item* rabbit_hide;
    static Item* armor_stand;
    static Item* iron_horse_armor;
    static Item* golden_horse_armor;
    static Item* diamond_horse_armor;
    static Item* lead;
    static Item* name_tag;
    static Item* command_block_minecart;
    static Item* mutton;
    static Item* cooked_mutton;
    static Item* banner;
    static Item* spruce_door;
    static Item* birch_door;
    static Item* jungle_door;
    static Item* acacia_door;
    static Item* dark_oak_door;
    static Item* record_13;
    static Item* record_cat;
    static Item* record_blocks;
    static Item* record_chirp;
    static Item* record_far;
    static Item* record_mall;
    static Item* record_mellohi;
    static Item* record_stal;
    static Item* record_strad;
    static Item* record_ward;
    static Item* record_11;
    static Item* record_wait;

    static void registerItem(ushort_t, string_t, Item*);

    static void registerItemBlock(Block*);

    static void registerItems();

    static void deregisterItems();

    static Item *getItem(Block*);

    static Item *getItem(ushort_t);

    static Item *getItem(string_t);

    static ushort_t getItemType(Item*);

    static ushort_t getItemType(string_t);

    static string_t getItemName(Item*);

    static string_t getItemName(ushort_t);

    Item();

    bool getHasSubtypes();

    ushort_t getMaxDamage();

    count_t getMaxStackSize();

    void onCreated(std::shared_ptr<ItemStack>, EntityPlayer*);

private:
    static std::unordered_map<Block*, Item*> blockToItem;
    static std::unordered_map<ushort_t, Item*> typeToItem;
    static std::unordered_map<string_t, Item*> nameToItem;
    static std::unordered_map<Item*, ushort_t> itemToType;
    static std::unordered_map<string_t, ushort_t> nameToType;
    static std::unordered_map<Item*, string_t> itemToName;
    static std::unordered_map<ubyte_t, string_t> typeToName;

    bool hasSubtypes = false;
    ushort_t maxDamage = 0;
    count_t maxStackSize = 64;

protected:
    Item *setHasSubtypes(bool);

    Item *setMaxDamage(ushort_t);

    Item *setMaxStackSize(count_t);
};

#endif /* defined(__Serveur__Item__) */
