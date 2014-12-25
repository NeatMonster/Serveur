#ifndef __Serveur__SlotData__
#define __Serveur__SlotData__

#include "NBTTag.h"
#include "ByteBuffer.h"

class SlotData
{
    public:
        SlotData();

        void read(ByteBuffer&);

        short_t itemID;

        byte_t itemCount;
        byte_t itemDamage;

        NBTTag* nbt;
};

#endif // __Serveur__SlotData__
