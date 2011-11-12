//---------------------------------------------------------------------------


#pragma hdrstop

#include <vector>
#include "PackSender.h"
#include "PackageContainer.h"
#include "ByteBuffer.h"
#include "ReviewerCommon.h"
#include "GameWorld.h"
#include "PackageCommon.h"
#include "Opcodes.h"
#include "SharedDefine.h"
#include "SharedMemInfo.h"

using namespace std;

//---------------------------------------------------------------------------

#pragma package(smart_init)


void            GetPackageFromDataPack(WOWPackage  *   pack, String packHead, String mark, AnsiString packContent)
{
	pack->SetPacketProxyType(PROXY_TYPE_WORLD);
    packHead = packHead.Trim();
    int head = 0;
    for(int i=0; i<NUM_MSG_TYPES; i++)
    {
        if(String(opcodeTable[i].name) == packHead)
        {
            head = i;
            break;
        }
	}

	bool isLargePacket = false;
	int recvHeadLen = 2;
    AnsiString result;
    if(mark == SEND_MARK)
    {
        result.SetLength(sizeof(ClientPktHeader)+packContent.Length());
    }
    else
	{
		int totalSize = packContent.Length()+2;
		if(totalSize > 0x7FFF)
		{
			isLargePacket = true;
			recvHeadLen = 3;
		}
		else
		{
			recvHeadLen = 2;
		}
		result.SetLength(recvHeadLen+totalSize);
    }

    WORD length = 0;
    if(mark == SEND_MARK)
    {
        length = sizeof(ClientPktHeader)-2+packContent.Length();
    }
    else
    {
        length = recvHeadLen+packContent.Length();
    }
	int pos = 0;
	if(isLargePacket)
	{
		WriteBYTE(result.c_str(), pos, 0x80|(0xFF &(length>>16)));
	}
    WriteBYTE(result.c_str(), pos, 0xFF &(length>>8));
    WriteBYTE(result.c_str(), pos, 0xFF & length);
    if(mark == SEND_MARK)
    {
        WriteDWORD(result.c_str(), pos, head);
    }
    else
    {
        WriteWORD(result.c_str(), pos, head);
    }
    WriteBuf(result.c_str(), pos, packContent.c_str(), packContent.Length());

    pack->SetData(result);
    pack->SetIndex(GetLogicPackIndex());
    pack->SetMark(mark);
    pack->SetOpCodeMsg(packHead);
    pack->SetOpCode(head);
}


PackSender::PackSender()
{
}

PackSender::~PackSender()
{
}

void	PackSender::SendCastSpellTarget(int spellid, DWORD mask, uint64 guid)
{
    ByteBuffer  data;
    data << uint8(0);   //cast_count
    data << uint32(spellid);     //spell_id
    data << uint8(0);
	data << uint32(mask);
	data.appendPackGUID(guid);
    this->SendPacket(SEND_MARK, CMSG_CAST_SPELL, data.contents(), data.size());
}

void    PackSender::SendCastSpell(int spellid)
{
    ByteBuffer  data;
    data << uint8(0);   //cast_count
    data << uint32(spellid);     //spell_id
    data << uint8(0);
    data << uint32(0);

    this->SendPacket(SEND_MARK, CMSG_CAST_SPELL, data.contents(), data.size());
}

void    PackSender::SendPacket(String markDir, int opcode, const unsigned char * lpdata, int len)
{
    this->SendPacket(markDir, opcode, AnsiString((char *)lpdata, len));
}

void    PackSender::ForceSendPacket(String markDir, int opcode, AnsiString data, int connectionIndex)
{
    PackageContainer * worldPackageContainer = NULL;
    worldPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(connectionIndex);
    if(!worldPackageContainer)
        return;

    WOWPackage   curPack;
    int head = opcode;
	AnsiString packContent = data;

	GetPackageFromDataPack(&curPack, LookupOpcodeName(opcode), markDir, data);
	SetLogicPackIndex(GetLogicPackIndex() + 1);

	curPack.SetForceSend(1);
    if(markDir == SEND_MARK)
    {
        worldPackageContainer->OnGetSendWOWPack(&curPack);
    }
    else
    {
        worldPackageContainer->OnGetRecvWOWPack(&curPack);
    }
}

void    PackSender::SendPacket(String mark, int opcode, AnsiString data)
{
    PackageContainer * worldPackageContainer = GetPackageContainerManager()->GetDefaultWorldPackageContainer();
    if(!worldPackageContainer)
        return;

    WOWPackage   curPack;
    int head = opcode;
	AnsiString packContent = data;

	GetPackageFromDataPack(&curPack, LookupOpcodeName(opcode), mark, data);
	SetLogicPackIndex(GetLogicPackIndex() + 1);

    if(mark == SEND_MARK)
    {
        worldPackageContainer->OnGetSendWOWPack(&curPack);
    }
    else
    {
        worldPackageContainer->OnGetRecvWOWPack(&curPack);
    }
}

void    PackSender::SendUseGameObject(uint64 objGuid)
{
    PackageContainer * worldPackageContainer = GetPackageContainerManager()->GetDefaultWorldPackageContainer();
    if(!worldPackageContainer)
        return;

    ByteBuffer  data;
    data << objGuid;
    this->SendPacket(SEND_MARK, CMSG_GAMEOBJ_USE, data.contents(), data.size());
}

void    PackSender::SendReportUseGameObject(uint64 objGuid)
{
    PackageContainer * worldPackageContainer = GetPackageContainerManager()->GetDefaultWorldPackageContainer();
    if(!worldPackageContainer)
        return;

    ByteBuffer  data;
    data << objGuid;
    this->SendPacket(SEND_MARK, CMSG_GAMEOBJ_REPORT_USE, data.contents(), data.size());
}

void    PackSender::SendAutoStoreLootItem(int index)
{
    PackageContainer * worldPackageContainer = GetPackageContainerManager()->GetDefaultWorldPackageContainer();
    if(!worldPackageContainer)
        return;
    ByteBuffer  data;
    data << BYTE(index);
	this->SendPacket(SEND_MARK, CMSG_AUTOSTORE_LOOT_ITEM, data.contents(), data.size());
}

void	PackSender::SendRecvOpenAllMap(uint64 guid)
{
	int maxCnt = PLAYER_END/8;
	if(maxCnt % 4)
		maxCnt = maxCnt / 4 + 1;
	else
		maxCnt = maxCnt / 4;

	ByteBuffer  data;
	data << uint32(1);
	data << uint8(UPDATETYPE_VALUES);
	data.appendPackGUID(guid);
	data << uint8(maxCnt);
	vector<BYTE> buf;
	buf.resize(maxCnt * 4);
	memset((void *)&buf[0], 0, buf.size());
	for(int i=0; i<64; i++)
	{
        WriteBit(&buf[0], buf.size(), PLAYER_EXPLORED_ZONES_1+i, 1);
	}
	data.append(&buf[0], buf.size());
	for(int i=0; i<64; i++)
	{
        data << uint32(-1);
	}

	this->SendPacket(RECV_MARK, SMSG_UPDATE_OBJECT, data.contents(), data.size());
}

void	PackSender::SendVisible(uint64 guid, int type, int visible)
{
	int maxCnt = PLAYER_END/8;
	if(maxCnt % 4)
		maxCnt = maxCnt / 4 + 1;
	else
		maxCnt = maxCnt / 4;

	ByteBuffer  data;
	data << uint32(1);
	data << uint8(UPDATETYPE_VALUES);
	data.appendPackGUID(guid);
	data << uint8(maxCnt);
	vector<BYTE> buf;
	buf.resize(maxCnt * 4);
	memset((void *)&buf[0], 0, buf.size());
	WriteBit(&buf[0], buf.size(), type, 1);
	data.append(&buf[0], buf.size());
	if(visible)
	{
		data << uint32(-1);
	}
	else
	{
		data << uint32(0);
	}
	this->SendPacket(RECV_MARK, SMSG_UPDATE_OBJECT, data.contents(), data.size());
}

void	PackSender::SendWho(AnsiString areaName, int minLV, int maxLV)
{
	ByteBuffer  data;
	data << uint32(minLV);
	data << uint32(maxLV);
	data << uint8(0);
	data << uint8(0);
	data << uint32(-1);
	data << uint32(-1);
	data << uint32(0);
	data << uint32(1);
	data << AnsiToUtf8(areaName).c_str();
	this->SendPacket(SEND_MARK, CMSG_WHO, data.contents(), data.size());
}

void	PackSender::SendChatMi(AnsiString tagName, AnsiString content)
{
	ByteBuffer  data;
	data << uint32(CHAT_MSG_WHISPER);
	data << uint32(LANG_COMMON);
	data << AnsiToUtf8(tagName).c_str();
	data << AnsiToUtf8(content).c_str();
	this->SendPacket(SEND_MARK, CMSG_MESSAGECHAT, data.contents(), data.size());
}

void	PackSender::BuildMovementPack(ByteBuffer *data, uint64 guid, uint32 moveFlags, uint32 moveFlags2, uint32 timeTick,
		float x, float y, float z, float o, uint32 fallTime, String mark)
{
	if(GetSharedMemInfo()->FindSelf()->Build != 10146)
	{
		data->appendPackGUID(guid);
	}
	else
	{
		if(mark != SEND_MARK)
		{
			data->appendPackGUID(guid);
		}
	}
	*data << uint32(moveFlags);
	*data << uint16(moveFlags2);
	*data << uint32(timeTick);
	*data << float(x);
	*data << float(y);
	*data << float(z);
	*data << float(o);
	*data << uint32(fallTime);
}

void	PackSender::SendMovementBoth(int opcode, uint64 guid, uint32 moveFlags, uint32 moveFlags2, uint32 timeTick,
		float x, float y, float z, float o, uint32 fallTime)
{
	{
		ByteBuffer  data(100);
		BuildMovementPack(&data, guid, moveFlags, moveFlags2, timeTick,
			x, y, z, o, fallTime, SEND_MARK);
		this->SendPacket(SEND_MARK, opcode, data.contents(), data.size());
	}

	{
		ByteBuffer  data(100);
		BuildMovementPack(&data, guid, moveFlags, moveFlags2, timeTick,
			x, y, z, o, fallTime, RECV_MARK);
		this->SendPacket(RECV_MARK, opcode, data.contents(), data.size());
	}
}

void	PackSender::SendToClientSetCanFly(uint64 guid)
{
	ByteBuffer  data;
	data.appendPackGUID(guid);
	data << uint32(0);
	this->SendPacket(RECV_MARK, SMSG_MOVE_SET_CAN_FLY, data.contents(), data.size());
}

void	PackSender::SendToClientUnSetCanFly(uint64 guid)
{
	ByteBuffer  data;
	data.appendPackGUID(guid);
	data << uint32(0);
	this->SendPacket(RECV_MARK, SMSG_MOVE_UNSET_CAN_FLY, data.contents(), data.size());
}

void	PackSender::SendToClientSetRunSpeedChange(uint64 guid, float speed)
{
	ByteBuffer  data;
	data.appendPackGUID(guid);
	data << uint32(0);
	data << (uint8)0;
	data << float(speed);
	this->SendPacket(RECV_MARK, SMSG_FORCE_RUN_SPEED_CHANGE, data.contents(), data.size());
}

void	PackSender::SendToClientMoveWaterWalk(uint64 guid)
{
	ByteBuffer  data;
	data.appendPackGUID(guid);
	data << uint32(0);
	this->SendPacket(RECV_MARK, SMSG_MOVE_WATER_WALK, data.contents(), data.size());
}

void	PackSender::SendToClientMoveLandWalk(uint64 guid)
{
	ByteBuffer  data;
	data.appendPackGUID(guid);
	data << uint32(0);
	this->SendPacket(RECV_MARK, SMSG_MOVE_LAND_WALK, data.contents(), data.size());
}
