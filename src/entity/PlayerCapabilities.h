#ifndef __Serveur__PlayerCapabilities__
#define __Serveur__PlayerCapabilities__

#include "NBTTagCompound.h"

class PlayerCapabilities
{
    public:
        PlayerCapabilities();

        void readCapabilitiesFromNBT(NBTTagCompound*);

    public:
        bool disableDamage;
        bool isFlying;
        bool allowFlying;
        bool isCreativeMode;
        bool allowEdit = true;

        float_t getFlySpeed();
        float_t getWalkSpeed();

    private:
        float_t flySpeed = 0.05F;
        float_t walkSpeed = 0.1F;
};

#endif // __Serveur__PlayerCapabilities__
