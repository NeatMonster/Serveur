#include "CraftingManager.h"

CraftingManager CraftingManager::instance;

CraftingManager &CraftingManager::getInstance() {
    return instance;
}
