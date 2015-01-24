#ifndef __Serveur__ItemSpade__
#define __Serveur__ItemSpade__

#include "ItemTool.h"

class ItemSpade : public ItemTool
{
    public:
        ItemSpade(ItemTool::ToolMaterial);

        bool canHarvestBlock(Block*);

    private:
        static const std::set<Block*> effectiveBlocks;
};

#endif // __Serveur__ItemSpade__
