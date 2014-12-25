#include "PacketCreativeInventoryAction.h"

#include "Logger.h"
#include "PacketHandler.h"

PacketCreativeInventoryAction::~PacketCreativeInventoryAction()
{
    delete clickedItem;
}

void PacketCreativeInventoryAction::read(ByteBuffer &buffer)
{
    buffer.getShort(slot);

    /*
     Pour ce paquet, de 9 à 35 pour les slots de l'inventaire standard.
     De 5 à 8 pour les emplacements d'armure.
     De 36 à 44 pour les emplacements de la quickbar.
     De 0 à 4 pour les emplacements de la table de craft intégrée à l'inventaire.
    */

    clickedItem = new SlotData();
    clickedItem->read(buffer);
}

void PacketCreativeInventoryAction::handle(PacketHandler *handler)
{
    handler->handleCreativeInventoryAction(this);
}
