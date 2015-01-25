#include "ItemHoe.h"

#include "CreativeTabs.h"

ItemHoe::ItemHoe(ItemTool::ToolMaterial toolMaterial) : toolMaterial(toolMaterial) {
    maxStackSize = 1;
    setMaxDamage(toolMaterial.getMaxUses());
    setCreativeTab(CreativeTabs::tabTools);
}
