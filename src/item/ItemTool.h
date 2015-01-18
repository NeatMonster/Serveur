#ifndef __Serveur__ItemTool__
#define __Serveur__ItemTool__

#include <set>

#include "Item.h"
#include "Block.h"

class ToolMaterial {
    public:
        static const ToolMaterial WOOD;
        static const ToolMaterial STONE;
        static const ToolMaterial IRON;
        static const ToolMaterial EMERALD;
        static const ToolMaterial GOLD;

    private:
        const int_t harvestLevel;
        const int_t maxUses;
        const float_t efficiency;
        const float_t damageVsEntity;
        const int_t enchantability;

        ToolMaterial(int_t harvestLevel, int_t maxUses, float_t efficiency, float_t damageVsEntity, int_t enchantability) :
            harvestLevel(harvestLevel), maxUses(maxUses), efficiency(efficiency), damageVsEntity(damageVsEntity), enchantability(enchantability)
        {}

    public:
        int_t getHarvestLevel();
        int_t getMaxUses();
        float_t getEfficiency();
        float_t getDamageVsEntity();
        int_t getEnchantability();
};


//----------------------------------------ItemTool---------------------------------------------


class ItemTool : public Item
{
    public:
        ItemTool(float_t, ToolMaterial, std::set<Block>);

    protected:
        ToolMaterial toolMaterial;
        float_t efficiency;

    private:
        float_t damageVsEntity;
        std::set<Block> effectiveBlocks;

    public:
        ToolMaterial getToolMaterial();
        float_t getEfficiency();
        float_t getDamageVsEntity();
        std::set<Block> getEffectiveBlocks();
};

#endif // __Serveur__ItemTool__
