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

const ToolMaterial ToolMaterial::WOOD = ToolMaterial(0, 59, 2.0F, 0.0F, 15);
const ToolMaterial ToolMaterial::STONE = ToolMaterial(1, 131, 4.0F, 1.0F, 5);
const ToolMaterial ToolMaterial::IRON = ToolMaterial(2, 250, 6.0F, 2.0F, 14);
const ToolMaterial ToolMaterial::EMERALD = ToolMaterial(3, 1561, 8.0F, 3.0F, 10);
const ToolMaterial ToolMaterial::GOLD = ToolMaterial(0, 32, 12.0F, 0.0F, 22);


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
};

#endif // __Serveur__ItemTool__
