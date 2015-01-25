#include "ItemAxe.h"

#include "ItemStack.h"

const std::set<Block*> ItemAxe::effectiveBlocks = {Block::planks, Block::bookshelf, Block::log, Block::log2,
    Block::chest, Block::pumpkin, Block::lit_pumpkin, Block::melon_block, Block::ladder};

ItemAxe::ItemAxe(ItemTool::ToolMaterial toolMaterial) : ItemTool(3., toolMaterial, effectiveBlocks) {}

float_t ItemAxe::getStrVsBlock(ItemStack* stack, Block* blockIn) {
    if(blockIn->getMaterial() != Material::wood && blockIn->getMaterial() != Material::plants && blockIn->getMaterial() != Material::vine)
        return ItemTool::getStrVsBlock(stack, blockIn);
    else
        return getEfficiency();
}
