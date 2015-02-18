#include "ItemPickaxe.h"

ItemPickaxe::ItemPickaxe(ItemTool::ToolMaterial toolMaterial) : ItemTool(2., toolMaterial, effectiveBlocks) {}

std::set<Block*> ItemPickaxe::effectiveBlocks = {Block::activator_rail, Block::coal_ore, Block::cobblestone,
    Block::detector_rail, Block::diamond_block, Block::diamond_ore, Block::double_stone_slab, Block::golden_rail,
    Block::gold_block, Block::gold_ore, Block::ice, Block::iron_block, Block::iron_ore, Block::lapis_block,
    Block::lapis_ore, Block::lit_redstone_ore, Block::mossy_cobblestone, Block::netherrack, Block::packed_ice,
    Block::rail, Block::redstone_ore, Block::sandstone, Block::red_sandstone, Block::stone, Block::stone_slab};

bool ItemPickaxe::canHarvestBlock(Block* blockIn) {
    return blockIn == Block::obsidian ? toolMaterial.getHarvestLevel() == 3 : (blockIn != Block::diamond_block && blockIn != Block::diamond_ore ? (blockIn != Block::emerald_ore && blockIn != Block::emerald_block ? (blockIn != Block::gold_block && blockIn != Block::gold_ore ? (blockIn != Block::iron_block && blockIn != Block::iron_ore ? (blockIn != Block::lapis_block && blockIn != Block::lapis_ore ? (blockIn != Block::redstone_ore && blockIn != Block::lit_redstone_ore ? (blockIn->getMaterial() == Material::rock ? true : (blockIn->getMaterial() == Material::iron ? true : blockIn->getMaterial() == Material::anvil)) : toolMaterial.getHarvestLevel() >= 2) : toolMaterial.getHarvestLevel() >= 1) : toolMaterial.getHarvestLevel() >= 1) : toolMaterial.getHarvestLevel() >= 2) : toolMaterial.getHarvestLevel() >= 2) : toolMaterial.getHarvestLevel() >= 2);
}

float_t ItemPickaxe::getStrVsBlock(Block* blockIn)
{
    if(blockIn->getMaterial() != Material::iron && blockIn->getMaterial() != Material::anvil && blockIn->getMaterial() != Material::rock)
        return ItemTool::getStrVsBlock(blockIn);
    else
        return getEfficiency();
}
