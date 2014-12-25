#include "Item.h"

Item::Item() : m_id(-1), m_count(0) {}

Item::Item(short_t id, short_t count) : m_id(id), m_count(count) {}

short_t Item::getID()
{
    return m_id;
}

short_t Item::getCount()
{
    return m_count;
}

void Item::setCount(short_t count)
{
    m_count = count;
}

void Item::setID(short_t id)
{
    m_id = id;
}

void Item::add(Item& item)
{
    if(m_id == item.getID() and m_count < STACK_SIZE-1)
        m_count++;
}
