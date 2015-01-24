#include "CreativeTabs.h"

std::vector<CreativeTabs*> CreativeTabs::creativeTabArray = std::vector<CreativeTabs*>();

CreativeTabs* CreativeTabs::tabBlock;
CreativeTabs* CreativeTabs::tabDecorations;
CreativeTabs* CreativeTabs::tabRedstone;
CreativeTabs* CreativeTabs::tabTransport;
CreativeTabs* CreativeTabs::tabMisc;
CreativeTabs* CreativeTabs::tabAllSearch;
CreativeTabs* CreativeTabs::tabFood;
CreativeTabs* CreativeTabs::tabTools;
CreativeTabs* CreativeTabs::tabCombat;
CreativeTabs* CreativeTabs::tabBrewing;
CreativeTabs* CreativeTabs::tabMaterials;
CreativeTabs* CreativeTabs::tabInventory;

void CreativeTabs::registerTabs() {
    (creativeTabArray = std::vector<CreativeTabs*>()).resize(12);

    tabBlock = new CreativeTabs(0, "buildingBlock");
    tabDecorations = new CreativeTabs(1, "decorations");
    tabRedstone = new CreativeTabs(2, "redstone");
    tabTransport = new CreativeTabs(3, "transportation");
    tabMisc = new CreativeTabs(4, "misc");
    tabAllSearch = new CreativeTabs(5, "search");
    tabFood = new CreativeTabs(6, "food");
    tabTools = new CreativeTabs(7, "tools");
    tabCombat = new CreativeTabs(8, "combat");
    tabBrewing = new CreativeTabs(9, "brewing");
    tabMaterials = new CreativeTabs(10, "materials");
    tabInventory = new CreativeTabs(11, "inventory");
}

void CreativeTabs::deregisterTabs() {
    for(auto tab : creativeTabArray)
        delete tab;
}

CreativeTabs::CreativeTabs(int_t index, string_t label) {
    tabIndex = index;
    tabLabel = label;
    creativeTabArray[tabIndex] = this;
}
