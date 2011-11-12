//---------------------------------------------------------------------------

#include <windows.h>
#pragma hdrstop

#include "MoveHandler.h"
#include "GameWorld.h"
#include "SharedDefine.h"
#include "FishAI.h"
#include "SharedMemInfo.h"
#include "FlyAI.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


MoveHandler::MoveHandler(GameWorld * gameWorld)
{
	m_HeartBeatTick = 0;
	m_OrgDiffTick = 0;
	m_LastMovementPackOptype = 0;
    m_GameWorld = gameWorld;

	REG_HANDLER(MSG_MOVE_START_FORWARD)
	REG_HANDLER(MSG_MOVE_START_BACKWARD)
	REG_HANDLER(MSG_MOVE_STOP)
    REG_HANDLER(MSG_MOVE_START_STRAFE_LEFT)
    REG_HANDLER(MSG_MOVE_START_STRAFE_RIGHT)       
    REG_HANDLER(MSG_MOVE_STOP_STRAFE)              
    REG_HANDLER(MSG_MOVE_JUMP)                     
    REG_HANDLER(MSG_MOVE_START_TURN_LEFT)          
    REG_HANDLER(MSG_MOVE_START_TURN_RIGHT)         
    REG_HANDLER(MSG_MOVE_STOP_TURN)                
    REG_HANDLER(MSG_MOVE_START_PITCH_UP)           
    REG_HANDLER(MSG_MOVE_START_PITCH_DOWN)
	REG_HANDLER(MSG_MOVE_STOP_PITCH)
    REG_HANDLER(MSG_MOVE_SET_RUN_MODE)
    REG_HANDLER(MSG_MOVE_SET_WALK_MODE)
    REG_HANDLER(MSG_MOVE_START_SWIM)
    REG_HANDLER(MSG_MOVE_STOP_SWIM)    
    REG_HANDLER(MSG_MOVE_FALL_LAND)
    REG_HANDLER(MSG_MOVE_HEARTBEAT)
    REG_HANDLER(MSG_MOVE_SET_FACING)
    REG_HANDLER(MSG_MOVE_SET_PITCH)
    REG_HANDLER(CMSG_MOVE_FALL_RESET)
    REG_HANDLER(CMSG_MOVE_SET_FLY)
    REG_HANDLER(MSG_MOVE_START_ASCEND)
    REG_HANDLER(MSG_MOVE_STOP_ASCEND)
    REG_HANDLER(CMSG_MOVE_CHNG_TRANSPORT)
    REG_HANDLER(MSG_MOVE_START_DESCEND)

	REG_HANDLER(SMSG_ENVIRONMENTALDAMAGELOG)

	REG_HANDLER(SMSG_FORCE_RUN_SPEED_CHANGE)
	REG_HANDLER(SMSG_FORCE_SWIM_SPEED_CHANGE)
	REG_HANDLER(CMSG_FORCE_RUN_SPEED_CHANGE_ACK)
	REG_HANDLER(SMSG_FORCE_FLIGHT_SPEED_CHANGE)

	REG_HANDLER(MSG_MOVE_SET_WALK_SPEED)
	REG_HANDLER(MSG_MOVE_SET_RUN_SPEED)
	REG_HANDLER(MSG_MOVE_SET_RUN_BACK_SPEED)
	REG_HANDLER(MSG_MOVE_SET_SWIM_SPEED)
	REG_HANDLER(MSG_MOVE_SET_SWIM_BACK_SPEED)
	REG_HANDLER(MSG_MOVE_SET_TURN_RATE)
	REG_HANDLER(MSG_MOVE_SET_FLIGHT_SPEED)
	REG_HANDLER(MSG_MOVE_SET_FLIGHT_BACK_SPEED)
	REG_HANDLER(MSG_MOVE_SET_PITCH_RATE)
    REG_HANDLER(SMSG_MOVE_KNOCK_BACK)
    REG_HANDLER(MSG_MOVE_KNOCK_BACK)
}

MoveHandler::~MoveHandler()
{
}

void    MoveHandler::Handler_MSG_MOVE_START_FORWARD(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_START_BACKWARD(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_STOP(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_START_STRAFE_LEFT(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_START_STRAFE_RIGHT(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_STOP_STRAFE(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_JUMP(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_START_TURN_LEFT(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_START_TURN_RIGHT(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_STOP_TURN(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_START_PITCH_UP(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_START_PITCH_DOWN(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_STOP_PITCH(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_SET_RUN_MODE(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_SET_WALK_MODE(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_FALL_LAND(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_START_SWIM(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_STOP_SWIM(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_HEARTBEAT(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_SET_FACING(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_SET_PITCH(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_CMSG_MOVE_FALL_RESET(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_CMSG_MOVE_SET_FLY(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_START_ASCEND(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_STOP_ASCEND(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_CMSG_MOVE_CHNG_TRANSPORT(WOWPackage * packet){HandlerMovementOpcodes(packet);}
void    MoveHandler::Handler_MSG_MOVE_START_DESCEND(WOWPackage * packet){HandlerMovementOpcodes(packet);}

void	MoveHandler::SetPos(uint64 guid, float x, float y, float z, float o)
{
	m_GameWorld->SetData(FormatStr("world/%llu/x", guid), x);
	m_GameWorld->SetData(FormatStr("world/%llu/y", guid), y);
	m_GameWorld->SetData(FormatStr("world/%llu/z",guid), z);
	m_GameWorld->SetData(FormatStr("world/%llu/o", guid), o);

	if(guid == m_GameWorld->GetSelfGUID())
	{
		m_GameWorld->SetData("self/posx", x);
		m_GameWorld->SetData("self/posy", y);
		m_GameWorld->SetData("self/posz", z);
		m_GameWorld->SetData("self/poso", o);
	}
}

void    MoveHandler::HandlerMovementOpcodes(WOWPackage * packet)
{
	int pos = 0;

	uint64 read_guid = 0;
	if(GetSharedMemInfo()->FindSelf()->Build != 10146)
	{
		READ_GUID(guid)
		read_guid = guid;
	}
	else
	{
		if(packet->GetMark() != SEND_MARK)
		{
			READ_GUID(guid);
			read_guid = guid;
		}
	}

	if(read_guid == 0)
	{
		read_guid = m_GameWorld->GetSelfGUID();
	}

//	#ifdef	WOW_FISHER
	{
		FishAI *fishAI = m_GameWorld->GetFishAI();
		if(fishAI->GetActive() && packet->GetMark() == SEND_MARK && (m_GameWorld->GetSelfGUID() == read_guid || read_guid == 0))
		{
			if(packet->GetOpCode() == MSG_MOVE_START_FORWARD || packet->GetOpCode() == MSG_MOVE_START_BACKWARD ||
				packet->GetOpCode() == MSG_MOVE_START_STRAFE_LEFT || packet->GetOpCode() == MSG_MOVE_START_STRAFE_RIGHT)
			{
				fishAI->PauseAI();
			}
		}
	}
//	#endif
	ReadMovementInfo(read_guid, packet, pos, NULL);
	m_LastMovementPackOptype = packet->GetOpCode();
	READ_FINISH
}


#define MAKE_MOVEMENTINFO_OPCODE(AINAME, REMOVE_FLAG) 	\
	if(GetGameWorld()->Get##AINAME()->GetActiveSetting() && guid == GetGameWorld()->GetSelfGUID() && (move_flags & REMOVE_FLAG))	\
	{	\
		int writePos = pos;	\
		move_flags ^= REMOVE_FLAG;	\
		WriteDWORD(packet->GetContent(), writePos, move_flags);	\
		packet->AddComment("Real Cast Flag : "#AINAME, GetMoveFlagComment(move_flags));      \
	}

void    MoveHandler::RemakeMovementInfo(uint64 guid, WOWPackage * packet, int pos, DWORD move_flags)
{
	if(packet->GetMark() != SEND_MARK)
	{
		return;
	}
	if(!GetGameWorld()->GetFlyAI()->GetActiveSetting())
	{
		return;
	}
	if(guid != GetGameWorld()->GetSelfGUID())
	{
		return;
	}
	DWORD org_move_flags = move_flags;
	MAKE_MOVEMENTINFO_OPCODE(WaterWalkingAI, MOVEFLAG_WATERWALKING)
	MAKE_MOVEMENTINFO_OPCODE(FlyAI, MOVEFLAG_CAN_FLY)
	MAKE_MOVEMENTINFO_OPCODE(FlyAI, MOVEFLAG_FLYING)
	MAKE_MOVEMENTINFO_OPCODE(FlyAI, MOVEFLAG_ASCENDING)

	if(packet->GetOpCode() == CMSG_MOVE_SET_FLY)
	{
		packet->SetProcessed(-1);
	}

	if(packet->GetOpCode() == MSG_MOVE_START_ASCEND)
	{
		packet->ChangeOPCode(MSG_MOVE_START_FORWARD);
		if(move_flags == 0)
		{
			int writePos = pos;
			move_flags = MOVEFLAG_FORWARD;
			WriteDWORD(packet->GetContent(), writePos, move_flags);
			packet->AddComment("Add Flag :", GetMoveFlagComment(move_flags));
		}
	}
	if(packet->GetOpCode() == MSG_MOVE_STOP_ASCEND)
	{
		packet->ChangeOPCode(MSG_MOVE_STOP);
	}

	if(org_move_flags & MOVEFLAG_FLYING)
	{
		packet->RemoveContent(packet->GetContentLen()-8, 4);
	}
}

void    MoveHandler::ReadMovementInfo(uint64 guid, WOWPackage * packet, int &pos, DWORD * move_flags_output)
{
	int obj_type_id = GuidHigh2TypeId(GUID_HIPART(guid));
	packet->GetComment()->Add(GetTypeIDName(obj_type_id));
	int writePos = pos;
	READ_TYPE(DWORD, move_flags, ReadDWORD);
	packet->GetComment()->Add(GetMoveFlagComment(move_flags));


    if(move_flags_output)
    {
        *move_flags_output = move_flags;
    }

    READ_TYPE(DWORD, move_flags2, ReadWORD);
	packet->GetComment()->Add(GetMoveFlag2Comment(move_flags2));

//	int tempPos = pos;
//	int time_tick_org = ReadDWORD(packet->GetContent(), tempPos);
//	tempPos -= 4;
//	if(packet->GetMark() == SEND_MARK && guid == m_GameWorld->GetSelfGUID())
//	{
//		DWORD	lastTick = m_OrgDiffTick;
//		packet->GetComment()->Add("---TickFix---");
//		packet->AddComment("OrgTimeTick", time_tick_org);
//		packet->AddComment("OrgDiff", time_tick_org - m_OrgDiffTick);
//		m_OrgDiffTick = time_tick_org;
//		if(GetSharedMemInfo()->FindSelf()->Build == 10146)
//		{
//			//movement tick 以500ms为等量间隔, 在这里使用自己的tick
//			if(packet->GetOpCode() == MSG_MOVE_HEARTBEAT)
//			{
//				//进行中
//				packet->AddComment("NewDiff", 500);
//				m_HeartBeatTick += 500;
//				WriteDWORD(packet->GetContent(), tempPos, m_HeartBeatTick);
//			}
//			else
//			{
//				if(m_LastMovementPackOptype == MSG_MOVE_HEARTBEAT)
//				{
//					DWORD diff = time_tick_org - m_HeartBeatTick;
//					diff = min(diff, DWORD(499));
//					packet->AddComment("NewDiffTurn", diff);
//					m_HeartBeatTick = m_HeartBeatTick + diff;
//					WriteDWORD(packet->GetContent(), tempPos, m_HeartBeatTick);
//				}
//				else
//				{
//					m_HeartBeatTick = time_tick_org;
//				}
//			}
//		}
//	}

	READ_TYPE(DWORD, time_tick, ReadDWORD)
	if(packet->GetMark() == RECV_MARK)
	{
		tagServerMSTimeMutiParam *param = m_GameWorld->GetServerMSTimeMutiParamData(STM_MOVEMENT_INFO);
		param->ServerMSTime = time_tick;
		param->MoveNPCName = GetObjectNameByGuid(guid);
	}

    READ_TYPE(float, posx, ReadFloat);
    READ_TYPE(float, posy, ReadFloat);
    READ_TYPE(float, posz, ReadFloat);
	READ_TYPE(float, poso, ReadFloat);
	SetPos(guid, posx, posy, posz, poso);


    if(move_flags & MOVEFLAG_ONTRANSPORT)
    {
        READ_GUID(t_guid)
        READ_TYPE(float, t_posx, ReadFloat);
        READ_TYPE(float, t_posy, ReadFloat);
        READ_TYPE(float, t_posz, ReadFloat);
        READ_TYPE(float, t_poso, ReadFloat);
        READ_TYPE(DWORD, t_time, ReadDWORD);
        READ_TYPE(int, t_seat, ReadBYTE);
        if(move_flags2 & MOVEFLAG2_UNK1)
        {
            READ_TYPE(DWORD, t_time2, ReadDWORD);
        }
    }

    if((move_flags & (MOVEFLAG_SWIMMING | MOVEFLAG_FLYING)) || (move_flags2 & MOVEFLAG2_ALLOW_PITCHING))
    {
        READ_TYPE(float, s_pitch, ReadFloat);
    }
    READ_TYPE(DWORD, fallTime, ReadDWORD)

    if(move_flags & MOVEFLAG_FALLING)
    {
        READ_TYPE(float, j_velocity, ReadFloat);
        READ_TYPE(float, j_cosAngle, ReadFloat);
        READ_TYPE(float, j_sinAngle, ReadFloat);
        READ_TYPE(float, j_xyspeed, ReadFloat);
    }

    if(move_flags & MOVEFLAG_SPLINE_ELEVATION)
    {
        READ_TYPE(float, u_unk1, ReadFloat);
	}

	RemakeMovementInfo(guid, packet, writePos, move_flags);
}
//////////////////////////////////////////////////////////////////////////////

void    MoveHandler::Handler_SMSG_ENVIRONMENTALDAMAGELOG(WOWPackage * packet)
{
    int pos = 0;
    READ_UINT64(guid)
    READ_BYTE(type)
    packet->GetComment()->Add(GetEnviromentalDamageName(type));
    READ_DWORD(damage);
    READ_DWORD(absorb);
    READ_DWORD(resisit);
    READ_FINISH
}

void    MoveHandler::Handler_SMSG_FORCE_RUN_SPEED_CHANGE(WOWPackage * packet)
{
	int pos = 0;
	READ_GUID(guid)
	READ_DWORD(zero)
	READ_BYTE(zero1)
	READ_FLOAT(speed)
	READ_FINISH
	if(guid == m_GameWorld->GetSelfGUID())
	{
		m_GameWorld->SetData("self/speed", speed);
	}
}

void    MoveHandler::Handler_SMSG_FORCE_SWIM_SPEED_CHANGE(WOWPackage * packet)
{
	int pos = 0;
	READ_GUID(guid)
	READ_DWORD(zero)
	READ_FLOAT(speed)
	READ_FINISH
}

void    MoveHandler::Handler_CMSG_FORCE_RUN_SPEED_CHANGE_ACK(WOWPackage * packet)
{
	int pos = 0;
	READ_GUID(guid)
	READ_DWORD(unk1)
	DWORD move_flags_output = 0;
	ReadMovementInfo(guid, packet, pos, &move_flags_output);
	READ_FLOAT(newspeed)
	READ_FINISH
	GetFiberManager()->Awake(FWC_WAIT_RUN_SPEED_CHANGE_ACK);
}

void    MoveHandler::Handler_SMSG_FORCE_FLIGHT_SPEED_CHANGE(WOWPackage * packet)
{
	int pos = 0;
	READ_GUID(guid)
	READ_DWORD(zero)
	READ_FLOAT(speed)
	READ_FINISH
}

void    MoveHandler::Handler_MSG_MOVE_SET_WALK_SPEED(WOWPackage *packet)
{
	Handler_MSG_MOVE_Change(packet);
}

void    MoveHandler::Handler_MSG_MOVE_SET_RUN_SPEED(WOWPackage *packet)
{
	Handler_MSG_MOVE_Change(packet);
}

void    MoveHandler::Handler_MSG_MOVE_SET_RUN_BACK_SPEED(WOWPackage *packet)
{
	Handler_MSG_MOVE_Change(packet);
}

void    MoveHandler::Handler_MSG_MOVE_SET_SWIM_SPEED(WOWPackage *packet)
{
	Handler_MSG_MOVE_Change(packet);
}

void    MoveHandler::Handler_MSG_MOVE_SET_SWIM_BACK_SPEED(WOWPackage *packet)
{
	Handler_MSG_MOVE_Change(packet);
}

void    MoveHandler::Handler_MSG_MOVE_SET_TURN_RATE(WOWPackage *packet)
{
	Handler_MSG_MOVE_Change(packet);
}

void    MoveHandler::Handler_MSG_MOVE_SET_FLIGHT_SPEED(WOWPackage *packet)
{
	Handler_MSG_MOVE_Change(packet);
}

void    MoveHandler::Handler_MSG_MOVE_SET_FLIGHT_BACK_SPEED(WOWPackage *packet)
{
	Handler_MSG_MOVE_Change(packet);
}

void    MoveHandler::Handler_MSG_MOVE_SET_PITCH_RATE(WOWPackage *packet)
{
	Handler_MSG_MOVE_Change(packet);
}


void    MoveHandler::Handler_MSG_MOVE_Change(WOWPackage *packet)
{
	int pos = 0;
	READ_GUID(guid)
	READ_DWORD(movementFlags)
	packet->AddComment("moveFlag", GetMoveFlagComment(movementFlags));
	READ_WORD(zero)
	READ_DWORD(timeTick)
	READ_FLOAT(X)
	READ_FLOAT(Y)
	READ_FLOAT(Z)
	READ_FLOAT(O)
	READ_DWORD(fallTime)
	READ_FLOAT(speed)
	READ_FINISH

	if(packet->GetMark() == RECV_MARK)
	{
		tagServerMSTimeMutiParam *param = m_GameWorld->GetServerMSTimeMutiParamData(STM_MSG_MOVE_SPEED_CHANGE);
		param->ServerMSTime = timeTick;
		param->MoveNPCName = GetObjectNameByGuid(guid);
	}
}

void    MoveHandler::Handler_SMSG_MOVE_KNOCK_BACK(WOWPackage *packet)
{
    int pos = 0;
    READ_GUID(guid)
    READ_DWORD(zero)
    READ_FLOAT(vcos)
    READ_FLOAT(vsin)
    READ_FLOAT(horizontalSpeed)
    READ_FLOAT(verticalSpeed)
    READ_FINISH
}

void    MoveHandler::Handler_MSG_MOVE_KNOCK_BACK(WOWPackage *packet)
{
    int pos = 0;
    READ_GUID(guid)
    ReadMovementInfo(guid, packet, pos, NULL);
    READ_FLOAT(cosAngle)
    READ_FLOAT(sinAngle)
    READ_FLOAT(xyspeed)
    READ_FLOAT(velocity)
    READ_FINISH
}
