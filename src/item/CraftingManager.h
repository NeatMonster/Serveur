#ifndef __Serveur__CraftingManager__
#define __Serveur__CraftingManager__

class CraftingManager {
public:
    static CraftingManager &getInstance();

private:
    static CraftingManager instance;
};

#endif /* defined(__Serveur__CraftingManager__) */
