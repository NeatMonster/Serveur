#ifndef __Serveur__ItemStack__
#define __Serveur__ItemStack__

#include "Block.h"
#include "Item.h"
#include "NBTTagCompound.h"
#include "Types.h"

class EntityPlayer;

class ItemStack : public std::enable_shared_from_this<ItemStack> {
    friend class PacketBuffer;

public:
    ItemStack(Item*);

    ItemStack(Item*, count_t);

    ItemStack(Item*, count_t, ushort_t);

    ItemStack(Block*);

    ItemStack(Block*, count_t);

    ItemStack(Block*, count_t, ushort_t);

    ItemStack(ItemStack*);

    Item* getItem();

    void setItem(Item*);

    count_t getCount();

    void setCount(count_t);

    ushort_t getDamage();

    void setDamage(ushort_t);

    std::shared_ptr<NBTTagCompound> getTag();

    void setTag(std::shared_ptr<NBTTagCompound>);

    bool hasTag();

    bool isDamageable();

    bool isDamaged();

    bool isStackable();

    count_t getMaxStackSize();

    void onCrafting(EntityPlayer*);

    std::shared_ptr<ItemStack> splitStack(count_t);

    bool equals(std::shared_ptr<ItemStack>);

    bool equals(std::shared_ptr<ItemStack>, bool);

    std::shared_ptr<ItemStack> clone();

private:
    Item *item;
    count_t count;
    ushort_t damage;
    std::shared_ptr<NBTTagCompound> tag;
};

#endif /* defined(__Serveur__ItemStack__) */
