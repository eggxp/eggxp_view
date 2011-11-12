//---------------------------------------------------------------------------

#ifndef ItemHandlerH
#define ItemHandlerH
//---------------------------------------------------------------------------

#include "Opcodes.h"
#include "PackageCommon.h"

class GameWorld;
class ItemHandler
{
private:
    GameWorld   *       m_GameWorld;
    void    Handler_SMSG_ITEM_QUERY_SINGLE_RESPONSE(WOWPackage * packet);
    void    Handler_SMSG_LOOT_RESPONSE(WOWPackage * packet);
    void    Handler_SMSG_LOOT_REMOVED(WOWPackage * packet);
    void    Handler_SMSG_ITEM_PUSH_RESULT(WOWPackage * packet);
	void    Handler_SMSG_LOOT_RELEASE_RESPONSE(WOWPackage * packet);
	void    Handler_SMSG_LIST_INVENTORY(WOWPackage * packet);
	void    Handler_SMSG_ITEM_COOLDOWN(WOWPackage * packet);

    void    ReadLootItem(int index, int packIndex, WOWPackage * packet, int &pos);
public:
    ItemHandler(GameWorld * gameworld);
    ~ItemHandler();

    void    ReadLootView(WOWPackage * packet, int &pos);
};


#endif
