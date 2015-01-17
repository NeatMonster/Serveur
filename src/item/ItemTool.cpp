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


// -------------------------------------- Item Tool ------------------------------------------------


ItemTool::ItemTool(float_t damageVsEntity, ToolMaterial material, std::set<Block> effectiveBlocks) : toolMaterial(material){
    this->damageVsEntity = this->toolMaterial.getDamageVsEntity() + damageVsEntity;
    this->maxStackSize = 1;
    this->maxDamage = this->toolMaterial.getMaxUses();
    this->efficiency = material.getEfficiency();
    this->effectiveBlocks = effectiveBlocks;
    //TODO : Associer le bon onglet CreativeTab
}
