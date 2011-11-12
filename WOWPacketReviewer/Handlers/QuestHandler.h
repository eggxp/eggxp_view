//---------------------------------------------------------------------------

#ifndef QuestHandlerH
#define QuestHandlerH
//---------------------------------------------------------------------------

#include "Opcodes.h"
#include "PackageCommon.h"

class GameWorld;
class QuestHandler
{
private:
    GameWorld   *       m_GameWorld;
	void    Handler_SMSG_QUESTGIVER_STATUS_MULTIPLE(WOWPackage * packet);
	void    Handler_SMSG_PAGE_TEXT_QUERY_RESPONSE(WOWPackage * packet);
	void    Handler_SMSG_QUESTGIVER_STATUS(WOWPackage * packet);
	void    Handler_SMSG_QUESTGIVER_QUEST_LIST(WOWPackage * packet);
	void    Handler_SMSG_QUESTGIVER_QUEST_DETAILS(WOWPackage * packet);
	void    Handler_SMSG_QUEST_QUERY_RESPONSE(WOWPackage * packet);
	void    Handler_SMSG_QUESTUPDATE_ADD_KILL(WOWPackage * packet);
	void    Handler_SMSG_QUESTGIVER_OFFER_REWARD(WOWPackage * packet);
	void    Handler_SMSG_QUESTGIVER_REQUEST_ITEMS(WOWPackage * packet);
	void    Handler_CMSG_GOSSIP_HELLO(WOWPackage * packet);
	void    Handler_CMSG_QUESTGIVER_QUERY_QUEST(WOWPackage * packet);
	void    Handler_CMSG_QUESTGIVER_CHOOSE_REWARD(WOWPackage * packet);
	void    Handler_SMSG_QUESTGIVER_QUEST_COMPLETE(WOWPackage * packet);
public:
    QuestHandler(GameWorld * gameworld);
    ~QuestHandler();
};


#endif
