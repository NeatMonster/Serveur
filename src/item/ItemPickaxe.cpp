#include "ItemPickaxe.h"

ItemPickaxe::ItemPickaxe(ItemTool::ToolMaterial toolMaterial) : ItemTool(2., toolMaterial, effectiveBlocks) {}

const std::set<Block*> ItemPickaxe::effectiveBlocks = {Block::activator_rail, Block::coal_ore, Block::cobblestone,
    Block::detector_rail, Block::diamond_block, Block::diamond_ore, Block::double_stone_slab, Block::golden_rail,
    Block::gold_block, Block::gold_ore, Block::ice, Block::iron_block, Block::iron_ore, Block::lapis_block,
    Block::lapis_ore, Block::lit_redstone_ore, Block::mossy_cobblestone, Block::netherrack, Block::packed_ice,
    Block::rail, Block::redstone_ore, Block::sandstone, Block::red_sandstone, Block::stone, Block::stone_slab};
