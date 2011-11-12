//---------------------------------------------------------------------------

#ifndef PlayerAuthHandlerH
#define PlayerAuthHandlerH
//---------------------------------------------------------------------------
#include "Opcodes.h"
#include "PackageCommon.h"

class GameWorld;
class PlayerAuthHandler
{
private:
    GameWorld   *       m_GameWorld;
	void    Handler_AUTH_LOGON_CHALLENGE(WOWPackage * packet);
	void    Handler_AUTH_LOGON_PROOF(WOWPackage * packet);
	void    Handler_REALM_LIST(WOWPackage * packet);
	void    Handler_SMSG_AUTH_CHALLENGE(WOWPackage * packet);
	void    Handler_CMSG_AUTH_SESSION(WOWPackage * packet);
	void    Handler_SMSG_AUTH_RESPONSE(WOWPackage * packet);
	void    Handler_SMSG_ADDON_INFO(WOWPackage * packet);
	void    Handler_SMSG_TUTORIAL_FLAGS(WOWPackage * packet);
	void    Handler_SMSG_REALM_SPLIT(WOWPackage * packet);
	void    Handler_CMSG_AUTH_SESSION_Decompressed(WOWPackage * packet);
    void    Handler_SMSG_REDIRECT_CLIENT(WOWPackage * packet);
    void    Handler_CMSG_REDIRECTION_FAILED(WOWPackage * packet);

	int		m_AddonsCount;
public:
    PlayerAuthHandler(GameWorld * gameworld);
    ~PlayerAuthHandler();
};

#endif
