#ifndef __Serveur__ItemTool__
#define __Serveur__ItemTool__

#include <set>

#include "Item.h"
#include "Block.h"

class ItemTool : public Item {
public:
    class ToolMaterial {
    public:
        static const ToolMaterial WOOD;
        static const ToolMaterial STONE;
        static const ToolMaterial IRON;
        static const ToolMaterial DIAMOND;
        static const ToolMaterial GOLD;

    private:
        const int_t harvestLevel;
        const int_t maxUses;
        const float_t efficiency;
        const float_t damageVsEntity;
        const int_t enchantability;

        ToolMaterial(int_t, int_t, float_t, float_t, int_t);

    public:
        int_t getHarvestLevel();

        int_t getMaxUses();

        float_t getEfficiency();

        float_t getDamageVsEntity();
        
        int_t getEnchantability();
    };

    ItemTool(float_t, ToolMaterial, std::set<Block*>);

    ToolMaterial getToolMaterial();

    float_t getEfficiency();

    float_t getDamageVsEntity();

    std::set<Block*> getEffectiveBlocks();

protected:
    ToolMaterial toolMaterial;
    float_t efficiency;

private:
    float_t damageVsEntity;
    std::set<Block*> effectiveBlocks;
};

#endif // __Serveur__ItemTool__
