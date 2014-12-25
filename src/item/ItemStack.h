#ifndef __Serveur__ItemStack__
#define __Serveur__ItemStack__

#include "NBTTagCompound.h"
#include "Types.h"

class ItemStack {
    friend class PacketBuffer;

public:
    ItemStack(short_t);

    ItemStack(short_t, byte_t);

    ItemStack(short_t, byte_t, short_t);

    short_t getType();

    byte_t getAmount();

    short_t getDamage();

    NBTTagCompound *getNBT();

private:
    short_t type;
    byte_t amount;
    short_t damage;
    NBTTagCompound *nbt;
};

#endif /* defined(__Serveur__ItemStack__) */
