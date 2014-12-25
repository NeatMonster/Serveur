#include "ItemGrid.h"

ItemGrid::ItemGrid(short_t size) : items(size)
{
    for(auto it = items.begin(); it != items.end(); it++)
        *it = new Item();
}

ItemGrid::~ItemGrid()
{
    for(auto it = items.begin(); it != items.end(); it++)
    {
        delete *it;
    }
}

Item *ItemGrid::getItem(short_t position)
{
    return items.at(position);
}
