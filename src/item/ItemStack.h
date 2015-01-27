#ifndef __Serveur__ItemStack__
#define __Serveur__ItemStack__

#include "NBTTagCompound.h"
#include "Types.h"

class ItemStack : public std::enable_shared_from_this<ItemStack> {
    friend class PacketBuffer;

public:
    ItemStack(short_t);

    ItemStack(short_t, byte_t);

    ItemStack(short_t, byte_t, short_t);

    ItemStack(ItemStack*);

    short_t getType();

    void setType(short_t);

    byte_t getAmount();

    void setAmount(byte_t);

    short_t getDamage();

    void setDamage(short_t);

    std::shared_ptr<NBTTagCompound> getNBT();

    std::shared_ptr<ItemStack> clone();

private:
    short_t type;
    byte_t amount;
    short_t damage;
    std::shared_ptr<NBTTagCompound> nbt;
};

#endif /* defined(__Serveur__ItemStack__) */
