//---------------------------------------------------------------------------


#pragma hdrstop

#include "Opcodes.h"
#include "GameWorld.h"
#include <map>
#include <string>
using namespace std;

//---------------------------------------------------------------------------

#pragma package(smart_init)

static map<int, String> gOpcodeDict;
static map<String, int> gOpcodeDictRevert;
static TStringList *gAllOpcodeNameList = new TStringList;

void InitOpcode()
{
	gOpcodeDict[0xFF00] = "SID_NULL";
	gOpcodeDict[0xFF02] = "SID_STOPADV";
	gOpcodeDict[0xFF04] = "SID_SERVERLIST";
	gOpcodeDict[0xFF05] = "SID_CLIENTID";
	gOpcodeDict[0xFF06] = "SID_STARTVERSIONING";
	gOpcodeDict[0xFF07] = "SID_REPORTVERSION";
	gOpcodeDict[0xFF08] = "SID_STARTADVEX";
	gOpcodeDict[0xFF09] = "SID_GETADVLISTEX";
	gOpcodeDict[0xFF0A] = "SID_ENTERCHAT";
	gOpcodeDict[0xFF0B] = "SID_GETCHANNELLIST";
	gOpcodeDict[0xFF0C] = "SID_JOINCHANNEL";
	gOpcodeDict[0xFF0E] = "SID_CHATCOMMAND";
	gOpcodeDict[0xFF0F] = "SID_CHATEVENT";
	gOpcodeDict[0xFF10] = "SID_LEAVECHAT";
	gOpcodeDict[0xFF12] = "SID_LOCALEINFO";
	gOpcodeDict[0xFF13] = "SID_FLOODDETECTED";
	gOpcodeDict[0xFF14] = "SID_UDPPINGRESPONSE";
	gOpcodeDict[0xFF15] = "SID_CHECKAD";
	gOpcodeDict[0xFF16] = "SID_CLICKAD";
	gOpcodeDict[0xFF17] = "SID_READMEMORY";
	gOpcodeDict[0xFF18] = "SID_REGISTRY";
	gOpcodeDict[0xFF19] = "SID_MESSAGEBOX";
	gOpcodeDict[0xFF1A] = "SID_STARTADVEX2";
	gOpcodeDict[0xFF1B] = "SID_GAMEDATAADDRESS";
	gOpcodeDict[0xFF1C] = "SID_STARTADVEX3";
	gOpcodeDict[0xFF1D] = "SID_LOGONCHALLENGEEX";
	gOpcodeDict[0xFF1E] = "SID_CLIENTID2";
	gOpcodeDict[0xFF1F] = "SID_LEAVEGAME";
	gOpcodeDict[0xFF20] = "SID_ANNOUNCEMENT";
	gOpcodeDict[0xFF21] = "SID_DISPLAYAD";
	gOpcodeDict[0xFF22] = "SID_NOTIFYJOIN";
	gOpcodeDict[0xFF23] = "SID_WRITECOOKIE";
	gOpcodeDict[0xFF24] = "SID_READCOOKIE";
	gOpcodeDict[0xFF25] = "SID_PING";
	gOpcodeDict[0xFF26] = "SID_READUSERDATA";
	gOpcodeDict[0xFF27] = "SID_WRITEUSERDATA";
	gOpcodeDict[0xFF28] = "SID_LOGONCHALLENGE";
	gOpcodeDict[0xFF29] = "SID_LOGONRESPONSE";
	gOpcodeDict[0xFF2A] = "SID_CREATEACCOUNT";
	gOpcodeDict[0xFF2B] = "SID_SYSTEMINFO";
	gOpcodeDict[0xFF2C] = "SID_GAMERESULT";
	gOpcodeDict[0xFF2D] = "SID_GETICONDATA";
	gOpcodeDict[0xFF2E] = "SID_GETLADDERDATA";
	gOpcodeDict[0xFF2F] = "SID_FINDLADDERUSER";
	gOpcodeDict[0xFF30] = "SID_CDKEY";
	gOpcodeDict[0xFF31] = "SID_CHANGEPASSWORD";
	gOpcodeDict[0xFF32] = "SID_CHECKDATAFILE";
	gOpcodeDict[0xFF33] = "SID_GETFILETIME";
	gOpcodeDict[0xFF34] = "SID_QUERYREALMS";
	gOpcodeDict[0xFF35] = "SID_PROFILE";
	gOpcodeDict[0xFF36] = "SID_CDKEY2";
	gOpcodeDict[0xFF3A] = "SID_LOGONRESPONSE2";
	gOpcodeDict[0xFF3C] = "SID_CHECKDATAFILE2";
	gOpcodeDict[0xFF3D] = "SID_CREATEACCOUNT2";
	gOpcodeDict[0xFF3E] = "SID_LOGONREALMEX";
	gOpcodeDict[0xFF3F] = "SID_STARTVERSIONING2";
	gOpcodeDict[0xFF40] = "SID_QUERYREALMS2";
	gOpcodeDict[0xFF41] = "SID_QUERYADURL";
	gOpcodeDict[0xFF43] = "SID_WARCRAFTSOMETHING";
	gOpcodeDict[0xFF44] = "SID_WARCRAFTGENERAL";
	gOpcodeDict[0xFF45] = "SID_NETGAMEPORT";
	gOpcodeDict[0xFF46] = "SID_NEWS_INFO";
	gOpcodeDict[0xFF4A] = "SID_OPTIONALWORK";
	gOpcodeDict[0xFF4B] = "SID_EXTRAWORK";
	gOpcodeDict[0xFF4C] = "SID_REQUIREDWORK";
	gOpcodeDict[0xFF4E] = "SID_TOURNAMENT";
	gOpcodeDict[0xFF50] = "SID_AUTH_INFO";
	gOpcodeDict[0xFF51] = "SID_AUTH_CHECK";
	gOpcodeDict[0xFF52] = "SID_AUTH_ACCOUNTCREATE";
	gOpcodeDict[0xFF53] = "SID_AUTH_ACCOUNTLOGON";
	gOpcodeDict[0xFF54] = "SID_AUTH_ACCOUNTLOGONPROOF";
	gOpcodeDict[0xFF55] = "SID_AUTH_ACCOUNTCHANGE";
	gOpcodeDict[0xFF56] = "SID_AUTH_ACCOUNTCHANGEPROOF";
	gOpcodeDict[0xFF57] = "SID_AUTH_ACCOUNTUPGRADE";
	gOpcodeDict[0xFF58] = "SID_AUTH_ACCOUNTUPGRADEPROOF";
	gOpcodeDict[0xFF59] = "SID_SETEMAIL";
	gOpcodeDict[0xFF5A] = "SID_RESETPASSWORD";
	gOpcodeDict[0xFF5B] = "SID_CHANGEEMAIL";
	gOpcodeDict[0xFF5C] = "SID_SWITCHPRODUCT";
	gOpcodeDict[0xFF5D] = "SID_REPORTCRASH";
	gOpcodeDict[0xFF5E] = "SID_WARDEN";
	gOpcodeDict[0xFF60] = "SID_GAMEPLAYERSEARCH";
	gOpcodeDict[0xFF65] = "SID_FRIENDSLIST";
	gOpcodeDict[0xFF66] = "SID_FRIENDSUPDATE";
	gOpcodeDict[0xFF67] = "SID_FRIENDSADD";
	gOpcodeDict[0xFF68] = "SID_FRIENDSREMOVE";
	gOpcodeDict[0xFF69] = "SID_FRIENDSPOSITION";
	gOpcodeDict[0xFF70] = "SID_CLANFINDCANDIDATES";
	gOpcodeDict[0xFF71] = "SID_CLANINVITEMULTIPLE";
	gOpcodeDict[0xFF72] = "SID_CLANCREATIONINVITATION";
	gOpcodeDict[0xFF73] = "SID_CLANDISBAND";
	gOpcodeDict[0xFF74] = "SID_CLANMAKECHIEFTAIN";
	gOpcodeDict[0xFF75] = "SID_CLANINFO";
	gOpcodeDict[0xFF76] = "SID_CLANQUITNOTIFY";
	gOpcodeDict[0xFF77] = "SID_CLANINVITATION";
	gOpcodeDict[0xFF78] = "SID_CLANREMOVEMEMBER";
	gOpcodeDict[0xFF79] = "SID_CLANINVITATIONRESPONSE";
	gOpcodeDict[0xFF7A] = "SID_CLANRANKCHANGE";
	gOpcodeDict[0xFF7B] = "SID_CLANSETMOTD";
	gOpcodeDict[0xFF7C] = "SID_CLANMOTD";
	gOpcodeDict[0xFF7D] = "SID_CLANMEMBERLIST";
	gOpcodeDict[0xFF7E] = "SID_CLANMEMBERREMOVED";
	gOpcodeDict[0xFF7F] = "SID_CLANMEMBERSTATUSCHANGE";
	gOpcodeDict[0xFF81] = "SID_CLANMEMBERRANKCHANGE";
	gOpcodeDict[0xFF82] = "SID_CLANMEMBERINFORMATION";
	gOpcodeDict[0xF701] = "W3GS_PING_FROM_HOST";
	gOpcodeDict[0xF704] = "W3GS_SLOTINFOJOIN";
	gOpcodeDict[0xF705] = "W3GS_REJECTJOIN";
	gOpcodeDict[0xF706] = "W3GS_PLAYERINFO";
	gOpcodeDict[0xF707] = "W3GS_PLAYERLEFT";
	gOpcodeDict[0xF708] = "W3GS_PLAYERLOADED";
	gOpcodeDict[0xF709] = "W3GS_SLOTINFO";
	gOpcodeDict[0xF70A] = "W3GS_COUNTDOWN_START";
	gOpcodeDict[0xF70B] = "W3GS_COUNTDOWN_END";
	gOpcodeDict[0xF70C] = "W3GS_INCOMING_ACTION";
	gOpcodeDict[0xF70F] = "W3GS_CHAT_FROM_HOST";
	gOpcodeDict[0xF71B] = "W3GS_LEAVERES";
	gOpcodeDict[0xF71E] = "W3GS_REQJOIN";
	gOpcodeDict[0xF721] = "W3GS_LEAVEREQ";
	gOpcodeDict[0xF723] = "W3GS_GAMELOADED_SELF";
	gOpcodeDict[0xF726] = "W3GS_OUTGOING_ACTION";
	gOpcodeDict[0xF727] = "W3GS_OUTGOING_KEEPALIVE";
	gOpcodeDict[0xF728] = "W3GS_CHAT_TO_HOST";
	gOpcodeDict[0xF72F] = "W3GS_SEARCHGAME";
	gOpcodeDict[0xF730] = "W3GS_GAMEINFO";
	gOpcodeDict[0xF731] = "W3GS_CREATEGAME";
	gOpcodeDict[0xF732] = "W3GS_REFRESHGAME";
	gOpcodeDict[0xF733] = "W3GS_DECREATEGAME";
	gOpcodeDict[0xF735] = "W3GS_PING_FROM_OTHERS";
	gOpcodeDict[0xF736] = "W3GS_PONG_TO_OTHERS";
	gOpcodeDict[0xF737] = "W3GS_CLIENTINFO";
	gOpcodeDict[0xF73D] = "W3GS_MAPCHECK";
	gOpcodeDict[0xF73F] = "W3GS_STARTDOWNLOAD";
	gOpcodeDict[0xF742] = "W3GS_MAPSIZE";
	gOpcodeDict[0xF743] = "W3GS_MAPPART";
	gOpcodeDict[0xF744] = "W3GS_MAPPARTOK";
	gOpcodeDict[0xF745] = "W3GS_MAPPARTNOTOK";
	gOpcodeDict[0xF746] = "W3GS_PONG_TO_HOST";
	gOpcodeDict[0xF748] = "W3GS_INCOMING_ACTION2";

	gOpcodeDict[0xF801] = "GPS_INIT";
	gOpcodeDict[0xF802] = "GPS_RECONNECT";
	gOpcodeDict[0xF803] = "GPS_ACK";
	gOpcodeDict[0xF804] = "GPS_REJECT";

	map<int, String>::iterator it;
	for (it = gOpcodeDict.begin(); it != gOpcodeDict.end(); ++it)
	{
		gOpcodeDictRevert[it->second.Trim().LowerCase()] = it->first;
		gAllOpcodeNameList->Add(it->second);
	}
}

String LookupOpcodeName(uint16 id)
{
	if (gOpcodeDict.find(id) != gOpcodeDict.end())
	{
		return gOpcodeDict[id];
	}
	return IntToHex(id, 10);
}

int LookupOpcodeID(String headStr)
{
	headStr = headStr.Trim().LowerCase();
	if (gOpcodeDictRevert.find(headStr) != gOpcodeDictRevert.end())
	{
		return gOpcodeDictRevert[headStr];
	}
	return StrToInt("$"+headStr);
}

TStringList *GetAllOpcodeNameList()
{
	return gAllOpcodeNameList;
}
