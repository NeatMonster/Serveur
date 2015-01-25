#ifndef __Serveur__CreativeTabs__
#define __Serveur__CreativeTabs__

#include "Types.h"

#include <vector>

class CreativeTabs
{
    public:
        static std::vector<CreativeTabs*> creativeTabArray;

        static CreativeTabs* tabBlock;
        static CreativeTabs* tabDecorations;
        static CreativeTabs* tabRedstone;
        static CreativeTabs* tabTransport;
        static CreativeTabs* tabMisc;
        static CreativeTabs* tabAllSearch;
        static CreativeTabs* tabFood;
        static CreativeTabs* tabTools;
        static CreativeTabs* tabCombat;
        static CreativeTabs* tabBrewing;
        static CreativeTabs* tabMaterials;
        static CreativeTabs* tabInventory;

        static void registerTabs();

        static void deregisterTabs();

        CreativeTabs(int_t, string_t);

    private:
        int_t tabIndex;
        string_t tabLabel;
};

#endif // __Serveur__CreativeTabs__
