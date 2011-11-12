//---------------------------------------------------------------------------


#pragma hdrstop

#include "WOWProxy.h"
#include "PlayerAuthHandler.h"
#include "GameWorld.h"
#include "SharedDefine.h"
#include "SharedMemInfo.h"
#include "ShareDef.h"
#include "zlib.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


PlayerAuthHandler::PlayerAuthHandler(GameWorld * gameWorld)
{
	m_AddonsCount = 0;
    m_GameWorld = gameWorld;
	REG_AUTH_HANDLER(AUTH_LOGON_CHALLENGE)
	REG_AUTH_HANDLER(AUTH_LOGON_PROOF)
	REG_AUTH_HANDLER(REALM_LIST)
	REG_HANDLER(SMSG_AUTH_CHALLENGE)
	REG_HANDLER(CMSG_AUTH_SESSION)
	REG_HANDLER(SMSG_AUTH_RESPONSE)
	REG_HANDLER(SMSG_ADDON_INFO)
	REG_HANDLER(SMSG_TUTORIAL_FLAGS)
	REG_HANDLER(SMSG_REALM_SPLIT)
    REG_HANDLER(SMSG_REDIRECT_CLIENT)
    REG_HANDLER(CMSG_REDIRECTION_FAILED)
}

PlayerAuthHandler::~PlayerAuthHandler()
{
}

void    PlayerAuthHandler::Handler_AUTH_LOGON_CHALLENGE(WOWPackage * packet)
{
	int pos = 0;
	if(packet->GetMark() == SEND_MARK)
	{
		READ_BYTE(cmd)
		READ_BYTE(error)
		READ_WORD(size)
		READ_STRING(gamename)
		READ_BYTE(version1)
		READ_BYTE(version2)
		READ_BYTE(version3)
		READ_WORD(build)
		READ_STRING(platform)
		READ_STRING(os)
		READ_BUFF(country, 4)
		packet->AddComment("country", country);
		for(int i=0; i<4; i++)
		{
			READ_BYTE(timezone_bias)
		}
		for(int i=0; i<4; i++)
		{
			READ_BYTE(ip)
		}
		READ_BYTE(I_len)
		READ_BUFF(Accid, I_len)
		packet->AddComment("AccID", Accid);
		READ_FINISH
		return;
	}
	if(packet->GetMark() == RECV_MARK)
	{
		READ_BYTE(cmd)
		READ_BYTE(zero)
		READ_BYTE(result)
		packet->AddComment("result", GetAuthResultName(result));
		if(result != WOW_SUCCESS)
		{
			READ_FINISH
			return;
		}
		READ_BUFF(B, 32)
		READ_BYTE(g_len)
		READ_BUFF(g, g_len)
		READ_BYTE(N_len)
		READ_BUFF(N, N_len)
		READ_BUFF(s, 32)
		READ_BUFF(unk3, 16)
		READ_BYTE(securityFlags)
		if(securityFlags & 0x01)                // PIN input
		{
			READ_DWORD(zero);
			READ_BUFF(hash, 16);
		}

		if(securityFlags & 0x02)                // Matrix input
		{
			READ_BYTE(z1)
			READ_BYTE(z2)
			READ_BYTE(z3)
			READ_BYTE(z4)
			READ_BUFF(z5, 8)
		}

		if(securityFlags & 0x04)                // Security token input
		{
			READ_BYTE(one1)
		}
		READ_FINISH
		return;
	}
}

void    PlayerAuthHandler::Handler_AUTH_LOGON_PROOF(WOWPackage * packet)
{
	int pos = 0;
	if(packet->GetMark() == SEND_MARK)
	{
		READ_BYTE(cmd)
		READ_BUFF(A, 32)
		READ_BUFF(M1, 20)
		READ_BUFF(crc_hash, 20)
		READ_BYTE(number_of_keys)
		READ_BYTE(securityFlags)
		READ_FINISH
		return;
	}
	if(packet->GetMark() == RECV_MARK)
	{
		READ_BYTE(cmd)
		READ_BYTE(error)
		READ_BUFF(M2, 20)
		READ_DWORD(unk1)
		READ_DWORD(unk2)
		READ_WORD(unk3)
		READ_FINISH
		return;
	}
}

void    PlayerAuthHandler::Handler_REALM_LIST(WOWPackage * packet)
{
	int pos = 0;
	if(packet->GetMark() == SEND_MARK)
	{
		READ_FINISH
		return;
	}
	if(packet->GetMark() == RECV_MARK)
	{
		READ_BYTE(cmd)
		READ_WORD(packetSize)

		READ_DWORD(zero)
		READ_WORD(realmSize)
		for(int i=0; i<realmSize; i++)
		{
			READ_BYTE(icon)
			READ_BYTE(lock)
			READ_BYTE(realmFlags)
			packet->AddComment("realmFlags", GetRealmFlagsName(realmFlags));
			READ_STRING(name)
			READ_STRING(address)
			READ_FLOAT(populationLevel)
			READ_BYTE(AmountOfCharacters)
			READ_BYTE(timezone)
			READ_BYTE(idMayBe)
			if (realmFlags & REALM_FLAG_SPECIFYBUILD)
			{
				READ_BYTE(major_version)
				READ_BYTE(minor_version)
				READ_BYTE(bugfix_version)
				READ_WORD(_build)
			}
			READ_WORD(split)
		}
		READ_FINISH
		return;
	}
}

void    PlayerAuthHandler::Handler_SMSG_AUTH_CHALLENGE(WOWPackage * packet)
{
	int pos = 0;
	READ_BYTE(one)
	READ_DWORD(seed)
	READ_BUFF(rand1, 16)
//	READ_BUFF(rand2, 16)
	READ_FINISH
}

void    PlayerAuthHandler::Handler_CMSG_AUTH_SESSION_Decompressed(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(addonsCount)
	m_AddonsCount = addonsCount;
	for(DWORD i=0; i<addonsCount; i++)
	{
		READ_STRING(addonName)
		READ_BYTE(enable)
		READ_DWORD(crc)
		READ_DWORD(unk1)
	}
	READ_DWORD(unk2)
	READ_FINISH;
}

void    PlayerAuthHandler::Handler_CMSG_AUTH_SESSION(WOWPackage * packet)
{
    int build = GetSharedMemInfo()->FindSelf()->Build;
	int pos = 0;
	READ_DWORD(ClientBuild)
	READ_DWORD(unk2)
	READ_STRING(account)
	READ_DWORD(unk3)
	READ_DWORD(clientSeed)
	READ_DWORD(unk5)
	READ_DWORD(unk6)
    if(build > 11723)
    {
    	READ_DWORD(unk7)
	    READ_BUFF(unk4, 8)
    }
	READ_BUFF(digest, 20)
	READ_DWORD(decompressedSize)
	uLongf uSize = decompressedSize;
	AnsiString decompressData;
	decompressData.SetLength(decompressedSize);
	if (uncompress(decompressData.c_str(), &uSize, packet->GetContent() + pos, packet->GetContentLen() - pos) != Z_OK)
	{
		packet->AddComment("Error", "Decompressed Error");
		return;
	}
	packet->SetDecompress(decompressData);
	Handler_CMSG_AUTH_SESSION_Decompressed(packet);
}

void    PlayerAuthHandler::Handler_SMSG_AUTH_RESPONSE(WOWPackage * packet)
{
	int pos = 0;
	READ_BYTE(response)
	packet->AddComment("response", GetResponseCodesName(response));
	if(response != AUTH_OK)
	{
		READ_FINISH
		return;
	}
	READ_DWORD(BillingTimeRemaining)
	READ_BYTE(BillingPlanFlags)
	READ_DWORD(BillingTimeRested)
	READ_BYTE(Expansion)
	READ_FINISH
}

void    PlayerAuthHandler::Handler_SMSG_ADDON_INFO(WOWPackage * packet)
{
	int pos = 0;
	packet->AddComment("m_AddonsCount", m_AddonsCount);
	for (int i=0; i<m_AddonsCount; i++)
	{
		packet->AddComment("------------------------index", i);
		READ_BYTE(state)
		READ_BYTE(unk1)
		if(unk1)
		{
			READ_BYTE(notStandard)
			if(notStandard)
			{
				READ_BUFF(publicKey, 256)
			}
			READ_DWORD(zero)
		}
		READ_BYTE(unk3)
		if (unk3)
		{
			READ_BYTE(zero1)
		}
	}
	READ_DWORD(BannedAddonsCount)
	READ_FINISH
}

void    PlayerAuthHandler::Handler_SMSG_TUTORIAL_FLAGS(WOWPackage * packet)
{
	int pos = 0;
	READ_FINISH
}

void    PlayerAuthHandler::Handler_SMSG_REALM_SPLIT(WOWPackage * packet)
{
	int pos = 0;
	READ_FINISH
}

void    PlayerAuthHandler::Handler_SMSG_REDIRECT_CLIENT(WOWPackage * packet)
{
    GetSharedMemInfo()->FindSelf()->ForbiddenAnyMortConnection = 1;
	int pos = 0;
    READ_BYTE(ip1)
    READ_BYTE(ip2)
    READ_BYTE(ip3)
    READ_BYTE(ip4)
    READ_WORD(port)
    READ_DWORD(U1)
    READ_BUFF(crc, 20)
	READ_FINISH
}

void    PlayerAuthHandler::Handler_CMSG_REDIRECTION_FAILED(WOWPackage * packet)
{
    GetSharedMemInfo()->FindSelf()->ForbiddenAnyMortConnection = 0;
    int pos = 0;
    READ_DWORD(u)
    READ_FINISH
}
