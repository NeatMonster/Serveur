#ifndef __Serveur__FoodStats__
#define __Serveur__FoodStats__

#include "NBTTagCompound.h"
#include "Types.h"

class EntityPlayer;
class ItemFood;
class ItemStack;

class FoodStats
{
    public:
        FoodStats();

        void onUpdate(EntityPlayer*);

        void addStats(varint_t, float_t);

        void addStats(ItemFood*, ItemStack*);

        void readNBT(NBTTagCompound&);

        void setFoodLevel(varint_t);

        varint_t getFoodLevel();

        bool needFood();

        float_t getSaturationLevel();

        void addExhaustion(float_t);

    private:
        int_t foodTimer;
        varint_t foodLevel;
        float_t saturationLevel;
        float_t exhaustionLevel;
};

#endif // __Serveur__FoodStats__
