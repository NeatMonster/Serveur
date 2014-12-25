#ifndef __Serveur__ItemGrid__
#define __Serveur__ItemGrid__

 #include "Item.h"

class ItemGrid
{
    public:
        ItemGrid(short_t);
        ~ItemGrid();

        Item* getItem(short_t position);

    protected:
        std::vector<Item*> items;
};

#endif // __Serveur__ItemGrid__
