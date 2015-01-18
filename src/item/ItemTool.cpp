#include "ItemTool.h"

int_t ToolMaterial::getHarvestLevel() {
    return harvestLevel;
}

int_t ToolMaterial::getMaxUses() {
    return maxUses;
}

float_t ToolMaterial::getEfficiency(){
    return efficiency;
}

float_t ToolMaterial::getDamageVsEntity() {
    return damageVsEntity;
}

int_t ToolMaterial::getEnchantability() {
    return enchantability;
}

const ToolMaterial ToolMaterial::WOOD = ToolMaterial(0, 59, 2.0F, 0.0F, 15);
const ToolMaterial ToolMaterial::STONE = ToolMaterial(1, 131, 4.0F, 1.0F, 5);
const ToolMaterial ToolMaterial::IRON = ToolMaterial(2, 250, 6.0F, 2.0F, 14);
const ToolMaterial ToolMaterial::EMERALD = ToolMaterial(3, 1561, 8.0F, 3.0F, 10);
const ToolMaterial ToolMaterial::GOLD = ToolMaterial(0, 32, 12.0F, 0.0F, 22);


// -------------------------------------- Item Tool ------------------------------------------------


ItemTool::ItemTool(float_t damageVsEntity, ToolMaterial material, std::set<Block> effectiveBlocks) : toolMaterial(material){
    this->damageVsEntity = this->toolMaterial.getDamageVsEntity() + damageVsEntity;
    this->maxStackSize = 1;
    this->maxDamage = this->toolMaterial.getMaxUses();
    this->efficiency = material.getEfficiency();
    this->effectiveBlocks = effectiveBlocks;
    //TODO : Associer le bon onglet CreativeTab
}

ToolMaterial ItemTool::getToolMaterial() {
    return toolMaterial;
}

float_t ItemTool::getEfficiency() {
    return efficiency;
}

float_t ItemTool::getDamageVsEntity() {
    return damageVsEntity;
}

std::set<Block> ItemTool::getEffectiveBlocks() {
    return effectiveBlocks;
}
