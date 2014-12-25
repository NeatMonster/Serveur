#include "SlotData.h"

SlotData::SlotData() : itemID(0), itemCount(0), itemDamage(0) {}

void SlotData::read(ByteBuffer &buffer)
{
    buffer.getShort(itemID);

    if(itemID == -1)
        return;

    buffer.getByte(itemCount);
    buffer.getByte(itemDamage);

    bytes_t nbtBytes;
    buffer.getBytes(nbtBytes);
    ubyte_t* ptr = (ubyte_t*)nbtBytes.data();

    /*
     * Le tag NBT est à implémenter plus tard.
     *
     * nbt = NBTTag::read(ptr);
     */
}
