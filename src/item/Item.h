#ifndef __Serveur__Item__
#define __Serveur__Item__

#include "Types.h"

#define STACK_SIZE 64

class Item
{
    public:
        Item();
        Item(short_t id, short_t count);

        void setID(short_t);
        void setCount(short_t);
        void add(Item& item);

        short_t getID();
        short_t getCount();
    protected:
        short_t m_id;
        short_t m_count;
};

#endif // __Serveur__Item__
