//---------------------------------------------------------------------------

#ifndef AuthPackageDispatcherH
#define AuthPackageDispatcherH
//---------------------------------------------------------------------------
#include <vcl.h>
#include "ReviewerCommon.h"
#include "PackageCommon.h"
#include "shareddefine.h"

#define MD5_DIGEST_LENGTH 16
#define ChunkSize 2048
#define AUTH_TOTAL_COMMANDS sizeof(table)/sizeof(AuthHandler)

#pragma pack(push,1)


typedef struct AUTH_LOGON_CHALLENGE_C
{
    uint8   cmd;
    uint8   error;
    uint16  size;
    uint8   gamename[4];
    uint8   version1;
    uint8   version2;
    uint8   version3;
    uint16  build;
    uint8   platform[4];
    uint8   os[4];
    uint8   country[4];
    uint32  timezone_bias;
    uint32  ip;
    uint8   I_len;
    uint8   I[1];
} sAuthLogonChallenge_C;

typedef struct AUTH_LOGON_PROOF_C
{
    uint8   cmd;
    uint8   A[32];
    uint8   M1[20];
    uint8   crc_hash[20];
    uint8   number_of_keys;
    uint8   securityFlags;                                  // 0x00-0x04
} sAuthLogonProof_C;

typedef struct AUTH_LOGON_PROOF_S
{
    uint8   cmd;
    uint8   error;
    uint8   M2[20];
    uint32  unk1;
    uint32  unk2;
    uint16  unk3;
} sAuthLogonProof_S;

typedef struct AUTH_LOGON_PROOF_S_BUILD_6005
{
    uint8   cmd;
    uint8   error;
    uint8   M2[20];
    //uint32  unk1;
    uint32  unk2;
    //uint16  unk3;
} sAuthLogonProof_S_BUILD_6005;

typedef struct AUTH_RECONNECT_PROOF_C
{
    uint8   cmd;
    uint8   R1[16];
    uint8   R2[20];
    uint8   R3[20];
    uint8   number_of_keys;
} sAuthReconnectProof_C;

typedef struct XFER_INIT
{
    uint8 cmd;                                              // XFER_INITIATE
    uint8 fileNameLen;                                      // strlen(fileName);
    uint8 fileName[5];                                      // fileName[fileNameLen]
    uint64 file_size;                                       // file size (bytes)
    uint8 md5[MD5_DIGEST_LENGTH];                           // MD5
}XFER_INIT;

typedef struct XFER_DATA
{
    uint8 opcode;
    uint16 data_size;
    uint8 data[ChunkSize];
}XFER_DATA_STRUCT;

class AuthPackageDispatcher;


typedef struct AuthHandler
{
    eAuthCmd cmd;
    const   char * name;
    int (AuthPackageDispatcher::*handler)(void);
}AuthHandler;

#pragma pack(pop)


class	AuthPackageDispatcher : public PackageDispatcher
{
//内部使用变量
private:
	WOWPackage				m_SendBufferPacket;
    WOWPackage				m_RecvBufferPacket;
    

//内部使用回调
private:
    

//内部使用函数
private:
    int                 DigestRecvBuffer();
    String              GetOPcodeMsgByCMD(uint8 cmd);
public:
	AuthPackageDispatcher();
	~AuthPackageDispatcher();


    int        _HandleLogonChallenge();
    int        _HandleLogonProof();
    int        _HandleReconnectChallenge();
    int        _HandleReconnectProof();
    int        _HandleRealmList();
    int        _HandleXferAccept();
    int        _HandleXferResume();
    int        _HandleXferCancel();


	//调用方法
public:
	void				GetOrignSendPacket(WOWPackage *  packet);
    void				GetOrignRecvPacket(WOWPackage *  packet);
	//打包发送
	void				PackData(char * buf, int len);
	void				Clear();
};


#endif
