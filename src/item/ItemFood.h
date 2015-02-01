#ifndef __Serveur__ItemFood__
#define __Serveur__ItemFood__

#include "EntityPlayer.h"
#include "Item.h"
#include "ItemStack.h"
#include "World.h"

class ItemFood : public Item
{
    public:
        ItemFood(int_t, float_t, bool);

        ItemStack* onItemRightClick(ItemStack*, World*, EntityPlayer*);

        ItemStack* onItemUseFinish(ItemStack*, World*, EntityPlayer*);

        varint_t getHealAmount();

        float_t getSaturationModifier();

        ItemFood* setAlwaysEdible(bool);

    private:
        varint_t healAmount;
        float_t saturationModifier;
        bool isWolfFavoriteMeat;
        bool alwaysEdible;

        int_t potionId;
        int_t potionDuration;
        int_t potionAmplifier;
};

#endif // __Serveur__ItemFood__
