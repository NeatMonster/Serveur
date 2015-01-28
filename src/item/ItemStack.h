#ifndef __Serveur__ItemStack__
#define __Serveur__ItemStack__

#include "Block.h"
#include "Item.h"
#include "NBTTagCompound.h"
#include "Types.h"

class ItemStack : public std::enable_shared_from_this<ItemStack> {
    friend class PacketBuffer;

public:
    ItemStack(Item*);

    ItemStack(Item*, byte_t);

    ItemStack(Item*, byte_t, short_t);

    ItemStack(Block*);

    ItemStack(Block*, byte_t);

    ItemStack(Block*, byte_t, short_t);

    ItemStack(ItemStack*);

    Item* getItem();

    void setItem(Item*);

    byte_t getCount();

    void setCount(byte_t);

    short_t getDamage();

    void setDamage(short_t);

    std::shared_ptr<NBTTagCompound> getTag();

    void setTag(std::shared_ptr<NBTTagCompound>);

    bool isStackable();

    std::shared_ptr<ItemStack> clone();

private:
    Item *item;
    byte_t count;
    short_t damage;
    std::shared_ptr<NBTTagCompound> tag;
};

#endif /* defined(__Serveur__ItemStack__) */
