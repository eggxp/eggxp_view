//---------------------------------------------------------------------------


#pragma hdrstop
#include <SysUtils.hpp>
#include "accprotocol.h"
#include "GenericFunc.h"
#include "CommFunc.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)

//CAccBase Class
//---------------------------------------------------------------------------
__fastcall CAccBase::CAccBase()
{
    m_IsEncryptPacket = true;
    m_lpCrypt = NewCryptClass(DATA_ENCRYPT_TYPE);
}
//---------------------------------------------------------------------------
__fastcall CAccBase::~CAccBase()
{
    delete m_lpCrypt;
}

//---------------------------------------------------------------------------
double    CAccBase::GetRandKey()
{
   return Now()-Now() % 1000;
}
//---------------------------------------------------------------------------
bool CAccBase::ReadHead(char *buf,int len,MSGHEAD &Head)
{
  //读取封包头
  if (len<MSG_HEAD_SIZE) //长度不足
  {
    return false;
  }
  CopyMemory(&Head,buf,MSG_HEAD_SIZE); //取得封包头信息
  if (Head.PackFlag != PACK_FLAG || len < Head.DataSize || Head.DataSize<MSG_HEAD_SIZE) //封包头不对或者封包不完整
  {
    return false;
  }
  return true; //读取封包头成功
}
//---------------------------------------------------------------------------
bool  CAccBase::CheckPacket(char *buf,int len)
{
   //校验封包合法性 合法返回0,非法返回非0
   //错误编号:
   //1 = 读取封包头失败
   //2 = 未知的命令封包
   //3 = 数据总长度不正确
   //4 =封包数据长度不正确
   //5 =封包MD5校验和失败
   MSGHEAD Head;
   if (!ReadHead(buf,len,Head))   //读取封包头失败
   {
      LastError =  "封包头错误";
      return false;
   }
   if (!IsValidityCmd(Head.Cmd))
   {
      LastError = FormatStr("未知命令 %d",Head.Cmd);
      return false;    //未知的命令封包
   }
   if (len < Head.DataSize)
   {
      LastError = FormatStr("长度错误 len = %d,datasize = %d",len,Head.DataSize);
      return false;                 //数据总长度不正确
   }
   int PacketDataLen = Head.DataSize - MSG_HEAD_SIZE;
   if (PacketDataLen<=0)        //封包数据长度不正确
   {
      LastError = FormatStr("PacketDataLen 错误 %d",PacketDataLen);
      return false;
   }
   //DumpString(String(buf,len),"d:\\serverloginall.dat");
   //DumpString(String(&buf[MSG_HEAD_SIZE],PacketDataLen),"d:\\serverlogin.dat");
   String DataMD5 = m_MD5.GetMD5(&buf[MSG_HEAD_SIZE],PacketDataLen);
   if (DataMD5 != Head.CmdMD5)
   {
      LastError = FormatStr("local md5[%s] !=remote md5[%s]",DataMD5,Head.CmdMD5);
      ZeroMemory(buf,len);
      return false;  //封包MD5校验和失败
   }
   return true;      //成功

}
//---------------------------------------------------------------------------
void   CAccBase::SetPacketEncryptMode(bool Mode)
{
     m_IsEncryptPacket = Mode;
}
//---------------------------------------------------------------------------
bool  CAccBase::GetPacketEncryptMode()
{
     return m_IsEncryptPacket;
}
//---------------------------------------------------------------------------
bool  CAccBase::IsValidityCmd(BYTE Cmd)
{
  TCmdType CmdType = (TCmdType)Cmd;
  return (CmdType == acLOGIN || CmdType == acCREATE_USER || CmdType == acSAVEPOINT || CmdType == acCMDBACK || CmdType ==  acQUERYCARD);
}
//---------------------------------------------------------------------------
int CAccBase::DecryptPacket(char *buf,int len,double RandKey)
{
   Xor_Sub(buf,len,(char *)&RandKey,sizeof(RandKey));
   return len;
}
//---------------------------------------------------------------------------
int CAccBase::EncryptPacket(char *buf,int len,double RandKey)
{
   Xor_Add(buf,len,(char *)&RandKey,sizeof(RandKey));
   return len;
}
#ifdef SERVER_CRYPT_SIDE
//---------------------------------------------------------------------------
//CAccServerProtocol Class
//---------------------------------------------------------------------------
__fastcall CAccServerProtocol::CAccServerProtocol()
{

}
//---------------------------------------------------------------------------
__fastcall CAccServerProtocol::~CAccServerProtocol()
{

}
//---------------------------------------------------------------------------
bool     CAccServerProtocol::ReadLoginCmd(char *buf,int len,PC_LOGIN_PACKET LoginPacket)
{
    if (!ReadHead(buf,len,LoginPacket->PackHead)) //封包头读取失败
    {
       return false;
    }
    if (LoginPacket->PackHead.Cmd != acLOGIN)
    {
       //登陆标志错误
       return false;
    }
    //读取RSA密钥
    CopyMemory(&LoginPacket->KeyLen,buf+MSG_HEAD_SIZE,RSA_KEY_BUFFER_LEN+1);
    if (LoginPacket->KeyLen > RSA_KEY_BUFFER_LEN)
    {
       //数据KeyLen长度过大
       return false;
    }
    String EncryptKey = String(LoginPacket->CryptKey,LoginPacket->KeyLen);
    //使用私钥解密,还原出数据加密Key
    EncryptKey = m_Rsa.PrivateDecrypt(EncryptKey);
    //解密数据
    m_lpCrypt->Init(EncryptKey);
    int HeadSize = MSG_HEAD_SIZE+RSA_KEY_BUFFER_LEN+1;
    String ClientLoginData =  String(&buf[HeadSize],len-HeadSize);
    ClientLoginData = m_lpCrypt->DecryptStr(ClientLoginData);
    int ClientLen = ClientLoginData.Length();
    if (ClientLen < C_LOGIN_PACKET_SIZE-HeadSize)
    {
       //解密完的数据长度错误
       return false;
    }
    //复制解密数据
    CopyMemory(LoginPacket,buf,MSG_HEAD_SIZE);
    CopyMemory(&LoginPacket->UserId,ClientLoginData.c_str(),C_LOGIN_PACKET_SIZE-HeadSize);
    return true;
}
//---------------------------------------------------------------------------
bool     CAccServerProtocol::ReadCreateUserCmd(char *buf,int len,PC_CREATE_USER_PACKET CreatePacket)
{
    if (!ReadHead(buf,len,CreatePacket->PackHead)) //封包头读取失败
    {
       return false;
    }
    if (CreatePacket->PackHead.Cmd != acCREATE_USER)
    {
       return false;
    }
    if (m_IsEncryptPacket)
    {
       DecryptPacket(&buf[MSG_HEAD_SIZE],CreatePacket->PackHead.DataSize-MSG_HEAD_SIZE,CreatePacket->PackHead.RandKey);
    }
    CopyMemory(CreatePacket,buf,CreatePacket->PackHead.DataSize);
    return true;
}
//---------------------------------------------------------------------------
bool   CAccServerProtocol::ReadSavePointCmd(char *buf,int len,PC_SAVE_POINT_PACKET SpPacket)
{
    if (!ReadHead(buf,len,SpPacket->PackHead)) //封包头读取失败
    {
       return false;
    }
    if (SpPacket->PackHead.Cmd != acSAVEPOINT)
    {
       return false;
    }
    if (m_IsEncryptPacket)
    {
       DecryptPacket(&buf[MSG_HEAD_SIZE],SpPacket->PackHead.DataSize-MSG_HEAD_SIZE,SpPacket->PackHead.RandKey);
    }
    CopyMemory(SpPacket,buf,SpPacket->PackHead.DataSize);
    return true;
}
//---------------------------------------------------------------------------
bool   CAccServerProtocol::ReadQueryCardCmd(char *buf,int len,PC_QUERY_CARD_PACKET SpPacket)
{
    if (!ReadHead(buf,len,SpPacket->PackHead)) //封包头读取失败
    {
       return false;
    }
    if (SpPacket->PackHead.Cmd != acQUERYCARD)
    {
       return false;
    }
    if (m_IsEncryptPacket)
    {
       DecryptPacket(&buf[MSG_HEAD_SIZE],SpPacket->PackHead.DataSize-MSG_HEAD_SIZE,SpPacket->PackHead.RandKey);
    }
    CopyMemory(SpPacket,buf,SpPacket->PackHead.DataSize);
    return true;
}
//------------------------------------------------------------------------------
String   CAccServerProtocol::MakeLoginReturn(S_LOGIN_PACKET &ServerData)
{
    //填充封包头
    ServerData.Head.PackHead.PackFlag = PACK_FLAG;
    ServerData.Head.PackHead.RandKey  = GetRandKey();
    ServerData.Head.PackHead.Cmd      = acLOGIN;
    //检查扩展数据是否正确
    if (ServerData.Head.ExDataLen != ServerData.ExData.Length())
    {
       ServerData.Head.ExDataLen = 0;
    }
    //计算实际数据长度 = 封包总长度-信息头长度
    int PackLen = S_LOGIN_PACKET_HEAD_SIZE -MSG_HEAD_SIZE;
    int KeyDataLen = RSA_KEY_BUFFER_LEN+1; //存放Key的数据长度
    //加密数据
     //生成根据注册id生成加密Key
       String EncryptKey =   MakeKeyByID(ServerData.Head.UserId);
       m_lpCrypt->Init(EncryptKey);
       //生成待加密缓冲区
       String EncryptData = String((char *)&ServerData.Head.ReturnCode,PackLen-KeyDataLen)+ServerData.ExData;
       //加密封包数据,但不包含封包信息头
       EncryptData = m_lpCrypt->EncryptStr(EncryptData);
       //加密Key使用RSA 1024位私钥加密保护
       EncryptKey = m_Rsa.PrivateEncrypt(EncryptKey);
       ServerData.Head.KeyLen = EncryptKey.Length();

    String PacketDataBuffer; //用来存放最终封包的缓冲区
    //计算加密后的封包长度  加密Key信息长度+加密后的数据长度
    PackLen =  KeyDataLen+EncryptData.Length();
    //设置缓冲区大小 = 封包头长度+封包数据长度
    PacketDataBuffer.SetLength(MSG_HEAD_SIZE+PackLen);
    ServerData.Head.PackHead.DataSize = PacketDataBuffer.Length();
    int Pos = MSG_HEAD_SIZE;
    //写入密钥数据
    WriteBYTE(PacketDataBuffer.c_str(),Pos,ServerData.Head.KeyLen);
    WriteBuf(PacketDataBuffer.c_str(),Pos,EncryptKey.c_str(),ServerData.Head.KeyLen);
    Pos = Pos+ (RSA_KEY_BUFFER_LEN-ServerData.Head.KeyLen);
    //写入加密后的数据
    WriteBuf(PacketDataBuffer.c_str(),Pos,EncryptData.c_str(),EncryptData.Length());
    //计算md5
    String MD5Str =  m_MD5.GetMD5((PacketDataBuffer.c_str()+MSG_HEAD_SIZE),PacketDataBuffer.Length()-MSG_HEAD_SIZE);
    memset(ServerData.Head.PackHead.CmdMD5,0,sizeof(ServerData.Head.PackHead.CmdMD5));
    wsprintf(ServerData.Head.PackHead.CmdMD5,"%s",MD5Str);
    //写入头信息
    CopyMemory(PacketDataBuffer.c_str(),&ServerData.Head.PackHead,sizeof(ServerData.Head.PackHead));
    return  PacketDataBuffer;
}
//---------------------------------------------------------------------------
String   CAccServerProtocol::MakeLoginReturn_Old(S_LOGIN_PACKET &ServerData)
{
    //填充封包头
    ServerData.Head.PackHead.PackFlag = PACK_FLAG;
    ServerData.Head.PackHead.RandKey  = GetRandKey();
    ServerData.Head.PackHead.Cmd      = acLOGIN;
    if (ServerData.Head.ExDataLen != ServerData.ExData.Length())
    {
       ServerData.Head.ExDataLen = 0;
    }
    int PackLen = S_LOGIN_PACKET_HEAD_SIZE + ServerData.Head.ExDataLen-MSG_HEAD_SIZE;
    String ReturnData;
    ServerData.Head.PackHead.DataSize = S_LOGIN_PACKET_HEAD_SIZE + ServerData.Head.ExDataLen;
    ReturnData.SetLength(ServerData.Head.PackHead.DataSize);
    char *lpbuf = ReturnData.c_str();
    int  DataPos=0;
    CopyMemory(&lpbuf[DataPos],&ServerData.Head,sizeof(ServerData.Head));
    DataPos += sizeof(ServerData.Head);
    CopyMemory(&lpbuf[DataPos],ServerData.ExData.c_str(),ServerData.ExData.Length());
    DataPos += sizeof(ServerData.ExData.Length());
    if (m_IsEncryptPacket) //是否加密封包
    {
       //生成根据注册id生成加密Key
       String EncryptKey =   MakeKeyByID(ServerData.Head.UserId);
       m_lpCrypt->Init(EncryptKey);
       //生成待加密缓冲区
       int KeyDataLen = RSA_KEY_BUFFER_LEN+1; //存放Key的数据长度
       String EncryptData = String(&lpbuf[MSG_HEAD_SIZE+KeyDataLen],PackLen-KeyDataLen);
       //加密封包数据,但不包含封包信息头
       EncryptData = m_lpCrypt->EncryptStr(EncryptData);
       //加密Key使用RSA 1024位私钥加密保护
       EncryptKey = m_Rsa.PrivateEncrypt(EncryptKey);
    }

    ZeroMemory(&ServerData.Head.PackHead.CmdMD5,sizeof(ServerData.Head.PackHead.CmdMD5));
    String MD5Str =  m_MD5.GetMD5(&lpbuf[MSG_HEAD_SIZE],PackLen);
    wsprintf(ServerData.Head.PackHead.CmdMD5,"%s",MD5Str);
    CopyMemory(lpbuf,&ServerData.Head.PackHead,sizeof(ServerData.Head.PackHead));
    return ReturnData;
}
//---------------------------------------------------------------------------
bool   CAccServerProtocol::MakeQueryReturn(S_QUERY_CARD_PACKET &ServerData)
{
    ServerData.PackHead.PackFlag = PACK_FLAG;
    ServerData.PackHead.RandKey  = GetRandKey();
    ServerData.PackHead.Cmd      = acQUERYCARD;

    int PackLen = sizeof(S_QUERY_CARD_PACKET) - MSG_HEAD_SIZE;
    ServerData.PackHead.DataSize = sizeof(S_QUERY_CARD_PACKET);
    if (m_IsEncryptPacket) //是否加密封包
    {
       //加密封包数据,但不包含封包信息头
       EncryptPacket(ServerData.CardNO,PackLen,ServerData.PackHead.RandKey);
    }
    ZeroMemory(&ServerData.PackHead.CmdMD5,sizeof(ServerData.PackHead.CmdMD5));
    String MD5Str =  m_MD5.GetMD5(ServerData.CardNO,PackLen);
    wsprintf(ServerData.PackHead.CmdMD5,"%s",MD5Str);
    return true;
}
//---------------------------------------------------------------------------
String  CAccServerProtocol::MakeKeyByID(String ID)
{
    String KeyOrg =  ID+IntToStr(GetCrc32(0,ID.c_str(),ID.Length()))+IntToStr(GetTickCount());
    return m_MD5.GetMD5(KeyOrg.c_str(),KeyOrg.Length());
}
//---------------------------------------------------------------------------
S_RETURN_PACKET  CAccServerProtocol::MakeCommBackCmd(int ReturnCode,BYTE CmdType)
{
    S_RETURN_PACKET  ServerData;
    ServerData.PackHead.PackFlag = PACK_FLAG;
    ServerData.PackHead.RandKey  = GetRandKey();
    ServerData.PackHead.Cmd      = CmdType;
    ServerData.ReturnCode        = ReturnCode;
    int PackLen = S_RETURN_PACKET_SIZE -MSG_HEAD_SIZE;
    ServerData.PackHead.DataSize = PackLen+MSG_HEAD_SIZE;
    if (m_IsEncryptPacket) //是否加密封包
    {
       //加密封包数据,但不包含封包信息头
       EncryptPacket((char *)&ServerData.ReturnCode,PackLen,ServerData.PackHead.RandKey);
    }
    ZeroMemory(&ServerData.PackHead.CmdMD5,sizeof(ServerData.PackHead.CmdMD5));
    String MD5Str =  m_MD5.GetMD5((char *)&ServerData.ReturnCode,PackLen);
    wsprintf(ServerData.PackHead.CmdMD5,"%s",MD5Str);
    return ServerData;
}
#endif
//---------------------------------------------------------------------------
//CAccClientProtocol Class
//---------------------------------------------------------------------------
__fastcall CAccClientProtocol::CAccClientProtocol()
{

}
//---------------------------------------------------------------------------
__fastcall CAccClientProtocol::~CAccClientProtocol()
{

}
//---------------------------------------------------------------------------
String  CAccClientProtocol::MakeLoginCmd(String UserId,String PassWord,BYTE ItemType,DWORD Reserve)
{
   C_LOGIN_PACKET LoginPacket;
   ZeroMemory(&LoginPacket,C_LOGIN_PACKET_SIZE);
   LoginPacket.PackHead.PackFlag = PACK_FLAG;
   LoginPacket.PackHead.RandKey  = GetRandKey();
   LoginPacket.PackHead.Cmd      = acLOGIN;
   wsprintf(LoginPacket.UserId,"%s",UserId);
   wsprintf(LoginPacket.UserPass,"%s",PassWord);
   LoginPacket.ItemType = ItemType;
   LoginPacket.Reserve  = Reserve;


    //计算实际数据长度 = 封包总长度+扩展数据长度-信息头长度
    int PackLen = C_LOGIN_PACKET_SIZE -MSG_HEAD_SIZE;
    int KeyDataLen = RSA_KEY_BUFFER_LEN+1; //存放Key的数据长度
     //加密数据
     //生成根据注册id生成加密Key
       String EncryptKey =   MakeKeyByID(LoginPacket.UserId);
       m_lpCrypt->Init(EncryptKey);
       //生成待加密缓冲区
       String EncryptData = String((char *)&LoginPacket.UserId,PackLen-KeyDataLen);
       //加密封包数据,但不包含封包信息头
       EncryptData = m_lpCrypt->EncryptStr(EncryptData);
       //加密Key使用RSA 1024位私钥加密保护
       EncryptKey = m_Rsa.PublicEncrypt(EncryptKey);
       LoginPacket.KeyLen = EncryptKey.Length();

    String PacketDataBuffer; //用来存放最终封包的缓冲区
    //计算加密后的封包长度  加密Key信息长度+加密后的数据长度
    PackLen =  KeyDataLen+EncryptData.Length();
    //设置缓冲区大小 = 封包头长度+封包数据长度
    PacketDataBuffer.SetLength(MSG_HEAD_SIZE+PackLen);
    LoginPacket.PackHead.DataSize = PacketDataBuffer.Length();
    int Pos = MSG_HEAD_SIZE;
    //写入密钥数据
    WriteBYTE(PacketDataBuffer.c_str(),Pos,LoginPacket.KeyLen);
    WriteBuf(PacketDataBuffer.c_str(),Pos,EncryptKey.c_str(),LoginPacket.KeyLen);
    Pos = Pos+ (RSA_KEY_BUFFER_LEN-LoginPacket.KeyLen);
    //写入加密后的数据
    WriteBuf(PacketDataBuffer.c_str(),Pos,EncryptData.c_str(),EncryptData.Length());
    //计算md5
    String MD5Str =  m_MD5.GetMD5((PacketDataBuffer.c_str()+MSG_HEAD_SIZE),PacketDataBuffer.Length()-MSG_HEAD_SIZE);
    //写入md5
    memset(LoginPacket.PackHead.CmdMD5,0,sizeof(LoginPacket.PackHead.CmdMD5));
    wsprintf(LoginPacket.PackHead.CmdMD5,"%s",MD5Str);
    //写入头信息
    CopyMemory(PacketDataBuffer.c_str(),&LoginPacket.PackHead,MSG_HEAD_SIZE);
    return  PacketDataBuffer;
}
//---------------------------------------------------------------------------
C_CREATE_USER_PACKET CAccClientProtocol::MakeCreateUserCmd(String UserId,String PassWord,String Email,BYTE GameType,DWORD Reserve)
{
    C_CREATE_USER_PACKET  ServerData;
    ZeroMemory(&ServerData,C_CREATE_USER_PACKET_SIZE);
    ServerData.PackHead.PackFlag = PACK_FLAG;
    ServerData.PackHead.RandKey  = GetRandKey();
    ServerData.PackHead.Cmd      = acCREATE_USER;
    wsprintf(ServerData.UserId,"%s",UserId);
    wsprintf(ServerData.UserPass,"%s",PassWord);
    wsprintf(ServerData.EMail,"%s",Email);
    ServerData.ItemType = GameType;
    ServerData.Reserve  = Reserve;
    int PackLen = C_CREATE_USER_PACKET_SIZE -MSG_HEAD_SIZE;
    ServerData.PackHead.DataSize = C_CREATE_USER_PACKET_SIZE;
    if (m_IsEncryptPacket) //是否加密封包
    {
       //加密封包数据,但不包含封包信息头
       EncryptPacket((char *)&ServerData.UserId,PackLen,ServerData.PackHead.RandKey);
    }
    String MD5Str = m_MD5.GetMD5((char *)&ServerData.UserId,PackLen);
    wsprintf(ServerData.PackHead.CmdMD5,"%s",MD5Str);
    return ServerData;
}
//---------------------------------------------------------------------------
C_SAVE_POINT_PACKET  CAccClientProtocol::MakeSavePointCmd(String CardNo,String CardPassWord,String UserId,String lgUserId,String PassWord,WORD CardType,BYTE GameType,int Reserve)
{
    C_SAVE_POINT_PACKET  ServerData;
    ZeroMemory(&ServerData,C_SAVE_POINT_PACKET_SIZE);
    ServerData.PackHead.PackFlag = PACK_FLAG;
    ServerData.PackHead.RandKey  = GetRandKey();
    ServerData.PackHead.Cmd      = acSAVEPOINT;
    wsprintf(ServerData.CardNo ,"%s",CardNo);
    wsprintf(ServerData.CardPass,"%s",CardPassWord);
    wsprintf(ServerData.UserId,"%s",UserId);
    wsprintf(ServerData.UserPass,"%s",PassWord);
    ServerData.Cardtype = CardType;
    ServerData.ItemType = GameType;
    ServerData.Reserve  = Reserve;
    int PackLen = C_SAVE_POINT_PACKET_SIZE -MSG_HEAD_SIZE;
    ServerData.PackHead.DataSize = C_SAVE_POINT_PACKET_SIZE;
    if (m_IsEncryptPacket) //是否加密封包
    {
       //加密封包数据,但不包含封包信息头
       EncryptPacket((char *)&ServerData.CardNo,PackLen,ServerData.PackHead.RandKey);
    }
    String MD5Str = m_MD5.GetMD5((char *)&ServerData.CardNo,PackLen);
    wsprintf(ServerData.PackHead.CmdMD5,"%s",MD5Str);
    return ServerData;
}
//---------------------------------------------------------------------------
bool   CAccClientProtocol::ReadLoginBackCmd(char * buf,int len,PS_LOGIN_PACKET LoginCmd)
{
    if (!CheckPacket(buf,len)) //封包头读取失败
    {
       return false;
    }
    if (!ReadHead(buf,len,LoginCmd->Head.PackHead))
    {
       return false;
    }
    if (LoginCmd->Head.PackHead.Cmd != acLOGIN)
    {
       return false;
    }
    //读取Key
    CopyMemory(&LoginCmd->Head.KeyLen,buf+MSG_HEAD_SIZE,RSA_KEY_BUFFER_LEN+1);
    if (LoginCmd->Head.KeyLen >RSA_KEY_BUFFER_LEN)
    {
       return false;
    }
    String EncryptKey = String((char *)&LoginCmd->Head.CryptKey,LoginCmd->Head.KeyLen);
    EncryptKey = m_Rsa.PublicDecrypt(EncryptKey);
    //破绽.....!!!!!!
    //在此处可以得到加密Key的明文 EncryptKey
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    m_lpCrypt->Init(EncryptKey);        //<---- 明文
    //头信息长度 封包头+RSAKey缓冲区长度+1
    int HeadLen =   MSG_HEAD_SIZE + RSA_KEY_BUFFER_LEN+1;
    //数据长度  =总长度-头长度
    int DataLen =  LoginCmd->Head.PackHead.DataSize - HeadLen;
    String EncryptData = String(buf+HeadLen,DataLen);
    EncryptData = m_lpCrypt->DecryptStr(EncryptData);
    #ifdef _DEBUG
    DumpString(EncryptData,"c:\\newlogin.dat");
    #endif
    m_lpCrypt->Init("");
    int DecryptDataLen = S_LOGIN_PACKET_HEAD_SIZE-HeadLen;
    if (EncryptData.Length() < DecryptDataLen)
    {
       return false;
    }
    //复制封包头
    CopyMemory(&LoginCmd->Head.PackHead,buf,sizeof(LoginCmd->Head.PackHead));
    //复制封包内容
    CopyMemory(&LoginCmd->Head.ReturnCode,EncryptData.c_str(),DecryptDataLen);
    //复制扩展数据
    if (LoginCmd->Head.ExDataLen>0)
    {
      LoginCmd->ExData.SetLength(LoginCmd->Head.ExDataLen);
      CopyMemory(LoginCmd->ExData.c_str(),EncryptData.c_str()+DecryptDataLen,LoginCmd->Head.ExDataLen);
    }
    return true;
}
//---------------------------------------------------------------------------
bool   CAccClientProtocol::ReadPackBackCmd(char *buf,int len,PS_RETURN_PACKET ReturnPack)
{
    if (!CheckPacket(buf,len) || !ReadHead(buf,len,ReturnPack->PackHead)) //封包头读取失败
    {
       return false;
    }
    if (m_IsEncryptPacket)
    {
       DecryptPacket(&buf[MSG_HEAD_SIZE],ReturnPack->PackHead.DataSize-MSG_HEAD_SIZE,ReturnPack->PackHead.RandKey);
    }
    CopyMemory(ReturnPack,buf,ReturnPack->PackHead.DataSize);
    return true;
}

//---------------------------------------------------------------------------
C_QUERY_CARD_PACKET  CAccClientProtocol::MakeQueryCardCmd(String CardNo,WORD CardType,BYTE GameType,int Reserve)
{
    C_QUERY_CARD_PACKET  ServerData;
    ZeroMemory(&ServerData,sizeof(C_QUERY_CARD_PACKET));
    ServerData.PackHead.PackFlag = PACK_FLAG;
    ServerData.PackHead.RandKey  = GetRandKey();
    ServerData.PackHead.Cmd      = acQUERYCARD;
    wsprintf(ServerData.CardNO,"%s",CardNo);
    ServerData.Cardtype = CardType;
    ServerData.ItemType = GameType;
    ServerData.Reserve  = Reserve;
    int PackLen = sizeof(C_QUERY_CARD_PACKET) -MSG_HEAD_SIZE;
    ServerData.PackHead.DataSize = sizeof(C_QUERY_CARD_PACKET);
    if (m_IsEncryptPacket) //是否加密封包
    {
       //加密封包数据,但不包含封包信息头
       EncryptPacket((char *)&ServerData.CardNO,PackLen,ServerData.PackHead.RandKey);
    }
    String MD5Str = m_MD5.GetMD5((char *)&ServerData.CardNO,PackLen);
    wsprintf(ServerData.PackHead.CmdMD5,"%s",MD5Str);
    return ServerData;
}
//---------------------------------------------------------------------------
bool      CAccClientProtocol::ReadQueryCardCmd(char *buf,int len,PS_QUERY_CARD_PACKET ReturnPack)
{
    if (!CheckPacket(buf,len) || !ReadHead(buf,len,ReturnPack->PackHead)) //封包头读取失败
    {
       return false;
    }
    if (ReturnPack->PackHead.Cmd !=acQUERYCARD)
    {
       return false;
    }
    if (m_IsEncryptPacket)
    {
       DecryptPacket(&buf[MSG_HEAD_SIZE],ReturnPack->PackHead.DataSize-MSG_HEAD_SIZE,ReturnPack->PackHead.RandKey);
    }
    CopyMemory(ReturnPack,buf,ReturnPack->PackHead.DataSize);
    return true;

}
//---------------------------------------------------------------------------
String  CAccClientProtocol::MakeKeyByID(String ID)
{
    return EncodeStr(ID+"=frmMain"+IntToStr(GetTickCount()));
}
