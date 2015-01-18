#ifndef __Serveur__ItemPickaxe__
#define __Serveur__ItemPickaxe__

#include "ItemTool.h"

class ItemPickaxe : public ItemTool
{
    public:
        ItemPickaxe(ToolMaterial);

    private:
        std::set<Block> effectiveBlocks; // TO DEFINE
};

#endif // __Serveur__ItemPickaxe__
