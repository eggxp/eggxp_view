//---------------------------------------------------------------------------


#pragma hdrstop

#include "AttackHandler.h"
#include "GameWorld.h"
#include "shareddefine.h"
#include "DBCStores.h"
#include "KOEItlbm.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)



AttackHandler::AttackHandler(GameWorld * gameworld)
{
    m_GameWorld = gameworld;
    REG_HANDLER(SMSG_ATTACKERSTATEUPDATE)
}

AttackHandler::~AttackHandler()
{
}

void    AttackHandler::Handler_SMSG_ATTACKERSTATEUPDATE(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(HitInfo)
	String HitInfoStr = GetHitInfoFlag(HitInfo);
	packet->GetComment()->Add(GetHitInfoFlag(HitInfo));
	READ_GUID(AttackerGUID)
	READ_GUID(TargetGUID)

	READ_DWORD(damage)
	READ_DWORD(overkill)
	READ_BYTE(count)
	for(int i=0; i<count; i++)
	{
		READ_DWORD(damageSchoolMask)
		READ_FLOAT(damageFloat)
		READ_DWORD(damageDWORD)
	}

	if(HitInfo & (HITINFO_ABSORB | HITINFO_ABSORB2))
	{
		for(int i = 0; i < count; ++i)
		{
			READ_DWORD(absorb)
		}
	}

	if(HitInfo & (HITINFO_RESIST | HITINFO_RESIST2))
	{
		for(int i = 0; i < count; ++i)
		{
			READ_DWORD(resist)
		}
	}

	READ_BYTE(TargetState)
	packet->GetComment()->Add(GetVictimState(TargetState));
	if(TargetGUID == m_GameWorld->GetSelfGUID())
	{
		m_GameWorld->SetData("attacker/guidl", DWORD(AttackerGUID & 0xFFFFFFFF));
		m_GameWorld->SetData("attacker/guidh", DWORD(AttackerGUID>>32));
//		#ifdef	WOW_FISHER
//		#ifdef 	_DEBUG
//		if(TargetState == VICTIMSTATE_PARRY)
//		{
//			GetFiberManager()->Awake(FWC_REACTION, FEC_DZ_ZHAOJIA);
//		}
//		#endif
//		#endif
	}
	READ_DWORD(Z1)
	READ_DWORD(Z2)
	if(HitInfo & HITINFO_BLOCK)
	{
		READ_DWORD(blocked_amount)
	}
	if(HitInfo & HITINFO_UNK3)
	{
		READ_DWORD(Z3)
	}
	if(HitInfo & HITINFO_UNK1)
	{
        READ_DWORD(Z4);
		READ_FLOAT(U1);
		READ_FLOAT(U2);
		READ_FLOAT(U3);
		READ_FLOAT(U4);
		READ_FLOAT(U5);
		READ_FLOAT(U6);
		READ_FLOAT(U7);
		READ_FLOAT(U8);
		for(uint8 i = 0; i < 5; ++i)
		{
			READ_FLOAT(U9);
			READ_FLOAT(U10);
		}
		READ_DWORD(Z5);
	}
	READ_FINISH

	if (AttackerGUID == m_GameWorld->GetSelfGUID() || TargetGUID == m_GameWorld->GetSelfGUID())
	{
		if (AttackerGUID == m_GameWorld->GetSelfGUID())
		{
			RefreshGridTotal(m_GameWorld, HitInfoStr, "normal", "attack");
		}
		else
		{
			RefreshGridTotal(m_GameWorld, HitInfoStr, "normal", "be_attack");
		}
	}
}
