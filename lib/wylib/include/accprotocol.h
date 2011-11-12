//---------------------------------------------------------------------------
//通信协议类,负责客户端和服务器端的通信协议,数据包生成,拆分,校验等工作
//By LinYi 2004.02.16

#ifndef accprotocolH
#define accprotocolH
#include <Windows.hpp>
#include <dstring.h>
#include "md5.h"
#include "cryptclass.h"
enum TCmdType {acLOGIN=0,acCREATE_USER,acSAVEPOINT,acCMDBACK,acQUERYCARD};
#pragma pack(push, 1)
#define RSA_KEY_BUFFER_LEN      200
#define DATA_ENCRYPT_TYPE 1  //数据加密算法 0=不加密,1=Des,2=Blowfish,3=BaseXorAdd,4=idea
#define MAX_USER_ID_LEN  31  //用户id最大长度
#define LOGIN_SUCCEED    0   //登陆成功
#define LOGIN_PASS_ERR   1  //用户名或密码错误
#define LOGIN_OVERTIME   3  //用户使用期限已过
#define LOGIN_QUERY_ERR  2 //查询数据库发生错误
#define LOGIN_WAIT_UPDATE  5 //等待软件更新


typedef struct tagMSGHEAD
{
  WORD DataSize;    //封包总大小
  WORD PackFlag;    //封包校验标志
  BYTE Cmd;         //命令编号
  double RandKey;   //随机密钥
  char CmdMD5[36];  //命令封包的MD5校验
}MSGHEAD,*PMSGHEAD;

typedef struct tagC_LOGIN_PACKET //从客户端来的登陆包
{
   MSGHEAD PackHead;           //封包头
   BYTE    KeyLen;           //数据解密key长度
   char    CryptKey[RSA_KEY_BUFFER_LEN];      //数据解密key内容
   char    UserId[MAX_USER_ID_LEN];         //用户Id
   char    UserPass[31];       //用户密码
   BYTE    ItemType;           //游戏编号
   DWORD   Reserve;            //保留
}C_LOGIN_PACKET,*PC_LOGIN_PACKET;


typedef struct tagS_LOGIN_PACKET_HEAD //从服务器端返回的登陆包头
{
   MSGHEAD PackHead;           //封包头
   BYTE    KeyLen;             //数据解密key长度
   char    CryptKey[RSA_KEY_BUFFER_LEN];      //数据解密key内容
   BYTE    ReturnCode;         //返回值
   char    UserId[MAX_USER_ID_LEN]; //用户Id
   int     LogNum;             //登陆次数
   double  SP;                 //剩余存储点数或到期时间
   WORD    ExDataLen;          //扩展数据长度
   DWORD   Reserve1;           //保留
   DWORD   Reserve2;           //保留
}S_LOGIN_PACKET_HEAD,*PS_LOGIN_PACKET_HEAD;

typedef struct tagC_CREATE_USER_PACKET //从客户端来的建立用户封包
{
   MSGHEAD PackHead;           //封包头
   char    UserId[MAX_USER_ID_LEN];         //用户Id
   char    UserPass[31];       //用户密码
   char    EMail[61];          //用户email
   BYTE    ItemType;           //类型编号
   DWORD   Reserve;            //保留
}C_CREATE_USER_PACKET,*PC_CREATE_USER_PACKET;

typedef struct tagC_SAVE_POINT_PACKET //从客户端来的储值封包
{
   MSGHEAD PackHead;           //封包头
   char    CardNo[31];         //卡号
   char    CardPass[31];       //密码
   char    UserId[MAX_USER_ID_LEN];          //用户名
   char    UserPass[31];       //用户密码
   WORD    Cardtype;           //卡类型
   BYTE    ItemType;           //类型编号
   DWORD   Reserve;            //保留
   char    lgUserID[31];       //受赠送卡号
}C_SAVE_POINT_PACKET,*PC_SAVE_POINT_PACKET;


typedef struct tagC_QUERY_CARD_PACKET    //从客户端发送的查询充值卡的封包
{
   MSGHEAD PackHead;           //封包头
   char    CardNO[11];
   WORD    Cardtype;
   WORD    ItemType;
   DWORD   Reserve;
}C_QUERY_CARD_PACKET,*PC_QUERY_CARD_PACKET;

typedef struct tagS_QUERY_CARD_PACKET    //从服务器端发送的查询充值卡的封包
{
   MSGHEAD PackHead;           //封包头
   char    CardNO[11];
   BYTE    Remain;            //剩余使用次数
   double  SaveDate;        //使用时间
   BYTE    FullTimes; 		//总使用次数
   char    UserId[210];  //充值记录
}S_QUERY_CARD_PACKET,*PS_QUERY_CARD_PACKET;

typedef struct tagS_RETURN_PACKET //从服务器端返回的通用包
{
   MSGHEAD PackHead;
   int     ReturnCode;
}S_RETURN_PACKET,*PS_RETURN_PACKET;

#pragma pack(pop)

#define  PACK_FLAG  0x6688
#define MSG_HEAD_SIZE                  sizeof(MSGHEAD)
#define C_LOGIN_PACKET_SIZE            sizeof(C_LOGIN_PACKET)
#define S_LOGIN_PACKET_HEAD_SIZE       sizeof(S_LOGIN_PACKET_HEAD)
#define C_CREATE_USER_PACKET_SIZE      sizeof(C_CREATE_USER_PACKET)
#define C_SAVE_POINT_PACKET_SIZE       sizeof(C_SAVE_POINT_PACKET)
#define S_RETURN_PACKET_SIZE           sizeof(S_RETURN_PACKET)

typedef struct tagS_LOGIN_PACKET //从服务器端返回的登陆包
{
   S_LOGIN_PACKET_HEAD Head;        //封包头
   String              ExData;
   String              ToString()  //生产缓冲区
   {
       String DataBuffer;
       char * pBuf;
       int  DataPos=0;
       DataBuffer.SetLength(sizeof(Head)+ExData.Length());
       pBuf =  DataBuffer.c_str();
       CopyMemory(&pBuf[DataPos],(char *)&Head,sizeof(Head));
       DataPos+=sizeof(Head);
       if (ExData.Length()>0)
       {
         CopyMemory(&pBuf[DataPos],ExData.c_str(),ExData.Length());
         DataPos+=ExData.Length();
       }
       return DataBuffer;
   }
}S_LOGIN_PACKET,*PS_LOGIN_PACKET;

class CAccBase
{
  private:
	  double		   LastRandKey;

  protected:
    WY_RSA       m_Rsa; //rsa加密类 ,保护加密Key
    WY_CryptBase * m_lpCrypt; //数据加密类 ,保护数据
    bool         m_IsEncryptPacket; //是否加密封包数据
    CMD5Checksum m_MD5;
    virtual double    GetRandKey();
    virtual bool IsValidityCmd(BYTE Cmd);      //校验命令合法性
    virtual int DecryptPacket(char *buf,int len,double RandKey) ;
    virtual int EncryptPacket(char *buf,int len,double RandKey) ;
    virtual String   MakeKeyByID(String ID)=0; //虚拟函数,客户端和服务器端根据用户id,生成加密数据key
  public:
    __fastcall CAccBase();
    __fastcall ~CAccBase();
    virtual bool       ReadHead(char *buf,int len,MSGHEAD &Head);       //读取封包头
    virtual bool       CheckPacket(char *buf,int len);   //校验封包合法性
    virtual void       SetPacketEncryptMode(bool Mode);   //设置加密模式
    virtual bool       GetPacketEncryptMode();            //获取加密模式
    virtual void       SetRSA_Key_EncryptKey(const String &Key){m_Rsa.SetKeyDataDecryptKey(Key);}
    virtual void       SetRSA_KeyData(const String &Key){m_Rsa.LoadEnKeyData(Key);}
	String     LastError;
	virtual double 			 GetLastRandKey(){return LastRandKey;}
};
#ifdef SERVER_CRYPT_SIDE
class CAccServerProtocol:public CAccBase //服务器端协议
{
private:
   double LoginRandKey;
protected:
  virtual String   MakeKeyByID(String ID);
public:
  __fastcall CAccServerProtocol();
  virtual __fastcall ~CAccServerProtocol();
  bool       ReadLoginCmd(char *buf,int len,PC_LOGIN_PACKET LoginPacket);
  bool       ReadCreateUserCmd(char *buf,int len,PC_CREATE_USER_PACKET CreatePacket);
  bool       ReadSavePointCmd(char *buf,int len,PC_SAVE_POINT_PACKET SpPacket);
  bool       ReadQueryCardCmd(char *buf,int len,PC_QUERY_CARD_PACKET SpPacket);
  String     MakeLoginReturn(S_LOGIN_PACKET &ServerData);
  String     MakeLoginReturn_Old(S_LOGIN_PACKET &ServerData); //旧版,弃用保留
  bool              MakeQueryReturn(S_QUERY_CARD_PACKET &ServerData);
  S_RETURN_PACKET    MakeCommBackCmd(int ReturnCode,BYTE CmdType);
  void       LoadPrivateKey(const String &PrivateKeyData){m_Rsa.LoadPrivateKey(PrivateKeyData);}
};
#endif
class CAccClientProtocol:public CAccBase //客户端用协议
{
private:

protected:
  virtual String   MakeKeyByID(String ID);
public:
  __fastcall CAccClientProtocol();
  virtual __fastcall ~CAccClientProtocol();
  virtual String  MakeLoginCmd(String UserId,String PassWord,BYTE ItemType,DWORD Reserve);
  virtual C_CREATE_USER_PACKET MakeCreateUserCmd(String UserId,String PassWord,String Email,BYTE GameType,DWORD Reserve);
  virtual C_SAVE_POINT_PACKET  MakeSavePointCmd(String CardNo,String CardPassWord,String UserId,String lgUserId,String PassWord,WORD CardType,BYTE GameType,int Reserve);
  virtual C_QUERY_CARD_PACKET  MakeQueryCardCmd(String CardNo,WORD CardType,BYTE GameType,int Reserve);
  virtual bool               ReadLoginBackCmd(char * buf,int len,PS_LOGIN_PACKET LoginCmd);
  virtual bool               ReadPackBackCmd(char *buf,int len,PS_RETURN_PACKET ReturnPack);
  virtual bool               ReadQueryCardCmd(char *buf,int len,PS_QUERY_CARD_PACKET ReturnPack);

};

DWORD DoubleValueCRC(double Crc);

//---------------------------------------------------------------------------
#endif
