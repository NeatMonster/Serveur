#ifndef __Serveur__ItemHoe__
#define __Serveur__ItemHoe__

#include "ItemTool.h"

class ItemHoe : public Item
{
    public:
        ItemHoe(ItemTool::ToolMaterial);

    protected:
        ItemTool::ToolMaterial toolMaterial;
};

#endif /* defined(__Serveur__ItemHoe__) */
