//---------------------------------------------------------------------------

#ifndef PlayerHandlerH
#define PlayerHandlerH
//---------------------------------------------------------------------------

#include "Opcodes.h"
#include "PackageCommon.h"
#include <map>
using namespace std;

struct tagWhoPlayerInfo
{
	String Player_Name;
	String Guild_Name;
	DWORD	level;
	DWORD	Class;
	DWORD	Race;
	DWORD	ZoneID;
	DWORD	MiTick;
	tagWhoPlayerInfo()
	{
		level = 0;
		Class = 0;
		Race = 0;
		ZoneID = 0;
		MiTick = 0;
	}
};

class GameWorld;
class PlayerHandler
{
private:
    GameWorld   *       m_GameWorld;
    void    Handler_SMSG_SET_PROFICIENCY(WOWPackage * packet);
    void    Handler_CMSG_PLAYER_LOGIN(WOWPackage * packet);
    void    Handler_CMSG_ACTIVATETAXI(WOWPackage * packet);
    void    Handler_SMSG_SHOWTAXINODES(WOWPackage * packet);
    void    Handler_SMSG_INIT_WORLD_STATES(WOWPackage * packet);
	void    Handler_SMSG_CHAR_ENUM(WOWPackage * packet);
	void    Handler_SMSG_ACCOUNT_DATA_TIMES(WOWPackage * packet);
	void    Handler_CMSG_UPDATE_ACCOUNT_DATA(WOWPackage * packet);
	void    Handler_SMSG_UPDATE_ACCOUNT_DATA(WOWPackage * packet);
	void    Handler_SMSG_WORLD_STATE_UI_TIMER_UPDATE(WOWPackage * packet);
	void    Handler_SMSG_QUERY_TIME_RESPONSE(WOWPackage * packet);
	void    Handler_SMSG_PLAYED_TIME(WOWPackage * packet);
	void    Handler_CMSG_TIME_SYNC_RESP(WOWPackage * packet);
	void    Handler_SMSG_LOGIN_SETTIMESPEED(WOWPackage * packet);
	void    Handler_CMSG_WHO(WOWPackage * packet);
	void    Handler_SMSG_WHO(WOWPackage * packet);
	void    Handler_CMSG_SET_SELECTION(WOWPackage * packet);
	void    Handler_SMSG_TRADE_STATUS_EXTENDED(WOWPackage * packet);
	void    Handler_SMSG_TALENTS_INFO(WOWPackage * packet);
	void    Handler_SMSG_POWER_UPDATE(WOWPackage * packet);
	void    Handler_SMSG_INITIALIZE_FACTIONS(WOWPackage * packet);
	void    Handler_SMSG_LOGIN_VERIFY_WORLD(WOWPackage * packet);
	void    Handler_CMSG_MOVE_SET_CAN_FLY_ACK(WOWPackage * packet);
	void    Handler_MSG_SET_DUNGEON_DIFFICULTY(WOWPackage * packet);
	void    Handler_SMSG_FEATURE_SYSTEM_STATUS(WOWPackage * packet);
	void    Handler_SMSG_MOTD(WOWPackage * packet);
	void    Handler_SMSG_LEARNED_DANCE_MOVES(WOWPackage * packet);
	void    Handler_SMSG_BINDPOINTUPDATE(WOWPackage * packet);
	void    Handler_SMSG_ACTION_BUTTONS(WOWPackage * packet);
	void    Handler_MSG_MOVE_TELEPORT_ACK(WOWPackage * packet);
	void    Handler_CMSG_MOVE_WATER_WALK_ACK(WOWPackage * packet);
	void    Handler_SMSG_MOVE_WATER_WALK(WOWPackage * packet);
	void    Handler_SMSG_MOVE_LAND_WALK(WOWPackage * packet);
	void    Handler_CMSG_LOGOUT_REQUEST(WOWPackage * packet);
	void    Handler_W3GS_GAMEINFO(WOWPackage * packet);

	map<String, tagWhoPlayerInfo>	m_WhoInfo;
public:
	void	CheckExpriedTime(DWORD time);
	void	CheckExpriedTimeByTimebit(DWORD timebit);
	void	CheckExpriedTime(int year, int month, int day, int hour, int min);
	void	CheckExpriedTime(TDateTime curtime);
	void    SetExpried();
    PlayerHandler(GameWorld * gameworld);
	~PlayerHandler();

	map<String, tagWhoPlayerInfo>   *GetWhoInfo(){return	&m_WhoInfo;}
};


#endif
