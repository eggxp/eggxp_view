//---------------------------------------------------------------------------


#pragma hdrstop

#include "AList.h"
#include "AuthLoader.h"
#include "CommFunc.h"
#include "VCL.h"
#include "AuthCrypt.h"
#include "BigNumber.h"



//---------------------------------------------------------------------------

#pragma package(smart_init)
static		AList<AuthCrypt>    gAuthCryptList;

AuthCrypt	*GetAuthCrypt(int connectionIndex)
{
    while(connectionIndex >= gAuthCryptList.Count())
    {
        gAuthCryptList.Add(new AuthCrypt);
    }
    return gAuthCryptList[connectionIndex];
}

//static      HANDLE      gDllHandle = NULL;

//typedef bool _cdecl  (*InitSeedType)(const char * sessionkey);
//typedef void _cdecl  (*DecryptType)(unsigned char *lpdata, int len);

void    LoadAuthDll()
{
//    if(gDllHandle)
//        return;
//
//    String dllPath = ExtractFilePath(Application->ExeName) + "WOWAuth.dll";
//    gDllHandle = LoadLibrary(dllPath.c_str());
//    if(gDllHandle == NULL)
//    {
//        ShowMessage(FormatStr("Load DLL Fail. %s", SysErrorMessage(GetLastError())));
//    }
}


bool	InitSeed(int connectionIndex, int build, AnsiString sessionkey)
{
    AuthCrypt	*gAuthCrypt = GetAuthCrypt(connectionIndex);
	BigNumber K;
	K.SetHexStr(sessionkey.c_str());
	if (build == 12340 || build == 11723 || build == 13507 || build == 13685 || build == 13930)
	{
		uint8 ServerEncryptionKey[SEED_KEY_SIZE] = { 0xCC, 0x98, 0xAE, 0x04, 0xE8, 0x97, 0xEA, 0xCA, 0x12, 0xDD, 0xC0, 0x93, 0x42, 0x91, 0x53, 0x57 };
		uint8 ServerDecryptionKey[SEED_KEY_SIZE] = { 0xC2, 0xB3, 0x72, 0x3C, 0xC6, 0xAE, 0xD9, 0xB5, 0x34, 0x3C, 0x53, 0xEE, 0x2F, 0x43, 0x67, 0xCE };
		gAuthCrypt->Init(&K, ServerEncryptionKey, ServerDecryptionKey);
	}
	else
	{
		uint8 ServerEncryptionKey[SEED_KEY_SIZE] = { 0x22, 0xBE, 0xE5, 0xCF, 0xBB, 0x07, 0x64, 0xD9, 0x00, 0x45, 0x1B, 0xD0, 0x24, 0xB8, 0xD5, 0x45 };
		uint8 ServerDecryptionKey[SEED_KEY_SIZE] = { 0xF4, 0x66, 0x31, 0x59, 0xFC, 0x83, 0x6E, 0x31, 0x31, 0x02, 0x51, 0xD5, 0x44, 0x31, 0x67, 0x98 };
		gAuthCrypt->Init(&K, ServerEncryptionKey, ServerDecryptionKey);
	}
	return	true;
}

bool	InitServerToClientSeed(int connectionIndex, int build, AnsiString sessionkey)
{
    AuthCrypt	*gAuthCrypt = GetAuthCrypt(connectionIndex);
    ASSERT(gAuthCrypt)
	BigNumber K;
	K.SetHexStr(sessionkey.c_str());
	if (build == 12340 || build == 11723 || build == 13507 || build == 13685)
	{
		uint8 ServerEncryptionKey[SEED_KEY_SIZE] = { 0xCC, 0x98, 0xAE, 0x04, 0xE8, 0x97, 0xEA, 0xCA, 0x12, 0xDD, 0xC0, 0x93, 0x42, 0x91, 0x53, 0x57 };
		gAuthCrypt->InitServerToClient(&K, ServerEncryptionKey);
	}
	else
	{
		uint8 ServerEncryptionKey[SEED_KEY_SIZE] = { 0x22, 0xBE, 0xE5, 0xCF, 0xBB, 0x07, 0x64, 0xD9, 0x00, 0x45, 0x1B, 0xD0, 0x24, 0xB8, 0xD5, 0x45 };
		gAuthCrypt->InitServerToClient(&K, ServerEncryptionKey);
	}
	return	true;
}

void	DecryptServerToClient(int connectionIndex, unsigned char *lpdata, int len)
{
    AuthCrypt	*gAuthCrypt = GetAuthCrypt(connectionIndex);
	if(!gAuthCrypt)
	{
		return;
	}
	gAuthCrypt->ServerToClientDecrypt(lpdata, len);
//	DecryptType func = (DecryptType)GetProcAddress(gDllHandle, "DecryptServerToClient");
//	func(lpdata, len);
//    return;
}

void	DecryptServerToClientEnd(int connectionIndex)
{
    AuthCrypt	*gAuthCrypt = GetAuthCrypt(connectionIndex);
	if(!gAuthCrypt)
	{
		return;
	}
	gAuthCrypt->ServerToClientDecryptOver();
}

void	DecryptClientToServer(int connectionIndex, unsigned char *lpdata, int len)
{
    AuthCrypt	*gAuthCrypt = GetAuthCrypt(connectionIndex);
	if(!gAuthCrypt)
	{
		return;
	}
	gAuthCrypt->ClientToServerDecrypt(lpdata, len);
//	DecryptType func = (DecryptType)GetProcAddress(gDllHandle, "DecryptClientToServer");
//	func(lpdata, len);
//    return;
}

void	EncryptServerToClient(int connectionIndex, unsigned char *lpdata, int len)
{
    AuthCrypt	*gAuthCrypt = GetAuthCrypt(connectionIndex);
	if(!gAuthCrypt)
	{
		return;
	}
	gAuthCrypt->ServerToClientEncrypt(lpdata, len);
//	DecryptType func = (DecryptType)GetProcAddress(gDllHandle, "EncryptServerToClient");
//	func(lpdata, len);
//    return;
}

void	EncryptClientToServer(int connectionIndex, unsigned char *lpdata, int len)
{
    AuthCrypt	*gAuthCrypt = GetAuthCrypt(connectionIndex);
	if(!gAuthCrypt)
	{
		return;
	}
	gAuthCrypt->ClientToServerEncrypt(lpdata, len);
//	DecryptType func = (DecryptType)GetProcAddress(gDllHandle, "EncryptClientToServer");
//	func(lpdata, len);
//    return;
}