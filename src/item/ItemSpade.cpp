#include "ItemSpade.h"

#include <set>

const std::set<Block*> ItemSpade::effectiveBlocks = {Block::clay, Block::dirt, Block::farmland, Block::grass,
    Block::gravel, Block::mycelium, Block::sand, Block::snow, Block::snow_layer, Block::soul_sand};

ItemSpade::ItemSpade(ItemTool::ToolMaterial toolMaterial) : ItemTool(1., toolMaterial, effectiveBlocks) {}

bool ItemSpade::canHarvestBlock(Block* blockIn) {
    if(blockIn == Block::snow_layer || blockIn == Block::snow)
        return true;
    else
        return false;
}
