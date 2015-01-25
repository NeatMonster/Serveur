#ifndef __Serveur__DataWatcher__
#define __Serveur__DataWatcher__

#include "ItemStack.h"
#include "Types.h"

#include <initializer_list>
#include <map>

class PacketBuffer;

class DataWatcher {
public:
    DataWatcher();

    ~DataWatcher();

    byte_t getByte(size_t);

    void setByte(size_t, byte_t);

    short_t getShort(size_t);

    void setShort(size_t, short_t);

    int_t getInt(size_t);

    void setInt(size_t, int_t);

    float_t getFloat(size_t);

    void setFloat(size_t, float_t);

    string_t getString(size_t);

    void setString(size_t, string_t);

    ItemStack *getItemStack(size_t);

    void setItemStack(size_t, ItemStack*);

    void read(PacketBuffer&);

    void write(PacketBuffer&);

private:
    enum {
        NONE = -1, BYTE, SHORT, INT, FLOAT, STRING, ITEMSTACK, INT_TUPLE, FLOAT_TUPLE
    };

    void *data[23];
    byte_t type[23];
};

#endif /* defined(__Serveur__DataWatcher__) */
