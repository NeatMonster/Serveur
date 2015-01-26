#ifndef __Serveur__ItemAxe__
#define __Serveur__ItemAxe__

#include "ItemTool.h"

#include <set>

class ItemAxe : public ItemTool
{
    public:
        ItemAxe(ItemTool::ToolMaterial);

        float_t getStrVsBlock(Block*);

    private:
        static const std::set<Block*> effectiveBlocks;
};

#endif // __Serveur__ItemAxe__
