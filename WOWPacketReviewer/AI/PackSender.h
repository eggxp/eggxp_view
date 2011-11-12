//---------------------------------------------------------------------------

#ifndef PackSenderH
#define PackSenderH
//---------------------------------------------------------------------------
#include <string>
#include "CommFunc.h"
using namespace std;
class ByteBuffer;
class WOWPackage;
void            GetPackageFromDataPack(WOWPackage  *   pack, String packHead, String mark, AnsiString packContent);

class PackSender
{
private:
	void	BuildMovementPack(ByteBuffer *data, uint64 guid, uint32 moveFlags, uint32 moveFlags2, uint32 timeTick,
		float x, float y, float z, float o, uint32 fallTime, String mark);
public:
    PackSender();
    ~PackSender();

    void    SendCastSpell(int spellid);

    void    SendPacket(String markDir, int opcode, const unsigned char * lpdata, int len);
	void    SendPacket(String markDir, int opcode, AnsiString data);
	void    ForceSendPacket(String markDir, int opcode, AnsiString data, int connectionIndex);
    void    SendUseGameObject(uint64 objGuid);
    void    SendReportUseGameObject(uint64 objGuid);
	void    SendAutoStoreLootItem(int index);
	void	SendCastSpellTarget(int spellid, DWORD mask, uint64 guid);
	void	SendRecvOpenAllMap(uint64 guid);
	void	SendVisible(uint64 guid, int type, int visible);
	void	SendWho(AnsiString areaName, int minLV, int maxLV);
	void	SendChatMi(AnsiString tagName, AnsiString content);
	void	SendMovementBoth(int opcode, uint64 guid, uint32 moveFlags, uint32 moveFlags2, uint32 timeTick,
		float x, float y, float z, float o, uint32 fallTime);
	void	SendToClientSetCanFly(uint64 guid);
	void	SendToClientUnSetCanFly(uint64 guid);
	void	SendToClientSetRunSpeedChange(uint64 guid, float speed);
	void	SendToClientMoveWaterWalk(uint64 guid);
	void	SendToClientMoveLandWalk(uint64 guid);

};

#endif
