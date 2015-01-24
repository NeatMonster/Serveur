#include "ItemTool.h"

const ItemTool::ToolMaterial ItemTool::ToolMaterial::WOOD(0, 59, 2., 0., 15);
const ItemTool::ToolMaterial ItemTool::ToolMaterial::STONE(1, 131, 4., 1., 5);
const ItemTool::ToolMaterial ItemTool::ToolMaterial::IRON(2, 250, 6., 2., 14);
const ItemTool::ToolMaterial ItemTool::ToolMaterial::DIAMOND(3, 1561, 8., 3., 10);
const ItemTool::ToolMaterial ItemTool::ToolMaterial::GOLD(0, 32, 12., 0., 22);

ItemTool::ToolMaterial::ToolMaterial(int_t harvestLevel, int_t maxUses, float_t efficiency,
                                     float_t damageVsEntity, int_t enchantability)
    : harvestLevel(harvestLevel), maxUses(maxUses), efficiency(efficiency),
      damageVsEntity(damageVsEntity), enchantability(enchantability) {}

int_t ItemTool::ToolMaterial::getHarvestLevel() {
    return harvestLevel;
}

int_t ItemTool::ToolMaterial::getMaxUses() {
    return maxUses;
}

float_t ItemTool::ToolMaterial::getEfficiency(){
    return efficiency;
}

float_t ItemTool::ToolMaterial::getDamageVsEntity() {
    return damageVsEntity;
}

int_t ItemTool::ToolMaterial::getEnchantability() {
    return enchantability;
}

ItemTool::ItemTool(float_t damageVsEntity, ToolMaterial material, std::set<Block*> effectiveBlocks) :
                   toolMaterial(material), effectiveBlocks(effectiveBlocks) {
    maxStackSize = 1;
    setMaxDamage(material.getMaxUses());
    this->damageVsEntity = damageVsEntity + material.getDamageVsEntity();
    efficiency = material.getEfficiency();
}

ItemTool::ToolMaterial ItemTool::getToolMaterial() {
    return toolMaterial;
}

float_t ItemTool::getEfficiency() {
    return efficiency;
}

float_t ItemTool::getDamageVsEntity() {
    return damageVsEntity;
}

float_t ItemTool::getStrVsBlock(ItemStack* stack, Block* blockIn) {
    if(effectiveBlocks.find(blockIn) != effectiveBlocks.end())
        return efficiency;
    else
        return 1.0F;
}

std::set<Block*> ItemTool::getEffectiveBlocks() {
    return effectiveBlocks;
}
