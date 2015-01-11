#ifndef __Serveur__EntityItem__
#define __Serveur__EntityItem__

#include "Entity.h"
#include "ItemStack.h"

class EntityItem : public Entity {
public:
    EntityItem(World*, ItemStack*);

    ~EntityItem();

    Type getType();

    ServerPacket *getSpawnPacket();

    void onTick();

private:
    ItemStack *stack;
};

#endif /* defined(__Serveur__EntityItem__) */
