#ifndef __Serveur__Inventory__
#define __Serveur__Inventory__

#include "ItemGrid.h"

class Inventory
{
public:
    Inventory();

    ItemGrid main; //Les 27 emplacements principaux.
    ItemGrid quickbar; //Les 9 emplacements de la quickbar.
    ItemGrid armor; //Les 4 emplacements de l'armure.
};

#endif /* defined(__Serveur__Inventory__) */
