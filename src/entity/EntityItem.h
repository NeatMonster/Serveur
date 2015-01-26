#ifndef __Serveur__EntityItem__
#define __Serveur__EntityItem__

#include "Entity.h"
#include "EntityPlayer.h"
#include "ItemStack.h"

class EntityItem : public Entity {
public:
    EntityItem(World*, ItemStack*);

    ~EntityItem();

    Type getType() { return ITEM; }

    int_t getTrackingRange() { return 64; }

    int_t getUpdateFrequency() { return 20; }

    bool sendVelocityUpdates() { return true; }

    std::shared_ptr<ServerPacket> getSpawnPacket();

    void onCollision(EntityPlayer*);

    void onTick();

private:
    ItemStack *stack;
    int_t pickupDelay;

    void searchForItems();

    bool combineItems(EntityItem*);
};

#endif /* defined(__Serveur__EntityItem__) */
