#ifndef __Serveur__EntityItem__
#define __Serveur__EntityItem__

#include "Entity.h"
#include "EntityPlayer.h"
#include "ItemStack.h"

class EntityItem : public Entity {
public:
    EntityItem(World*, std::shared_ptr<ItemStack>);

    Type getType() { return ITEM; }

    int_t getTrackingRange() { return 64; }

    int_t getUpdateFrequency() { return 20; }

    bool sendVelocityUpdates() { return true; }

    void fromCreative();

    std::shared_ptr<ItemStack> getItem();

    void setItem(std::shared_ptr<ItemStack>);

    std::shared_ptr<ServerPacket> getSpawnPacket();

    void onCollision(EntityPlayer*);

    void onTick();

private:
    int_t age;
    int_t pickupDelay;

    void searchForItems();

    bool combineItems(EntityItem*);
};

#endif /* defined(__Serveur__EntityItem__) */
