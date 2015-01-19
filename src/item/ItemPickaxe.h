#ifndef __Serveur__ItemPickaxe__
#define __Serveur__ItemPickaxe__

#include "ItemTool.h"

class ItemPickaxe : public ItemTool {
public:
    ItemPickaxe(ToolMaterial);

private:
    static const std::set<Block*> effectiveBlocks;
};

#endif // __Serveur__ItemPickaxe__
