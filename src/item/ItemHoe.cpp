#include "ItemHoe.h"

ItemHoe::ItemHoe(ItemTool::ToolMaterial toolMaterial) : toolMaterial(toolMaterial) {
    setMaxStackSize(1);
    setMaxDamage(toolMaterial.getMaxUses());
}
