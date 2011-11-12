//---------------------------------------------------------------------------

#ifndef ClientServerSharedH
#define ClientServerSharedH
//---------------------------------------------------------------------------
#include <vcl.h>

#define AUTH_SERVER_LIST_PORT   54887

enum	TClientServerPackType
{
	PT_MSG = 0,
	PT_AUTH,
	PT_C_REQ_ADDR_INFO,
	PT_C_REQ_CHARGE,
	PT_S_REQ_CHARGE,
};

#define	CHARGE_CARD_SIZE_MIN 40
#define	CHARGE_CARD_SIZE_MAX 55

#define AUTH_SEED_KEY_SIZE 16

static unsigned char WOWWGUserServerEncryptionKey[AUTH_SEED_KEY_SIZE] = { 0x23, 0xB8, 0xE5, 0xCF, 0xBB, 0x07, 0x64, 0xD9, 0x00, 0x4A, 0x1B, 0xD0, 0x24, 0xB0, 0xD5, 0x45 };
static unsigned char WOWWGUserServerDecryptionKey[AUTH_SEED_KEY_SIZE] = { 0xF4, 0x66, 0x32, 0x59, 0xFC, 0x83, 0x6E, 0x30, 0x31, 0x02, 0x51, 0xD5, 0x44, 0x3F, 0x67, 0x98 };

#pragma pack(push, 1)
struct	tagCClientAuth
{
	BYTE    U[24];
	char	UserName[50];
	BYTE    U2[10];
	BYTE	IsChargeProcess;
	BYTE	A[32];
	DWORD	Build;
	BYTE    U3[25];
	tagCClientAuth()
	{
		srand(time(NULL));
		memset(this, 0, sizeof(*this));
		for(DWORD i=0; i<sizeof(U); i++)
		{
			U[i] = rand()%255;
		}

		for(DWORD i=0; i<sizeof(U2); i++)
		{
			U2[i] = rand()%(127 - 33) + 33;
		}

		for(DWORD i=0; i<sizeof(U3); i++)
		{
			U3[i] = rand()%(127 - 33) + 33;
		}
	}
};

struct	tagSClientAuth
{
	BYTE    U[24];
	BYTE	s[32];
	BYTE    U2[10];
	BYTE	B[32];
	BYTE    U3[25];
	tagSClientAuth()
	{
		srand(time(NULL));
		memset(this, 0, sizeof(*this));
		for(DWORD i=0; i<sizeof(U); i++)
		{
			U[i] = rand()%255;
		}

		for(DWORD i=0; i<sizeof(U2); i++)
		{
			U2[i] = rand()%(127 - 33) + 33;
		}

		for(DWORD i=0; i<sizeof(U3); i++)
		{
			U3[i] = rand()%(127 - 33) + 33;
		}
	}
};

struct  tagCAuthCheck
{
	BYTE	M[20];
	tagCAuthCheck()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct  tagSAuthCheck
{
	BYTE	M2[20];
	tagSAuthCheck()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct	tagClientAddrInfo
{
	DWORD   Address;
	DWORD	Offset;
	double 	ExpireTime;
	tagClientAddrInfo()
	{
		memset(this, 0, sizeof(*this));
	}
};

#pragma pack(pop)



#endif
