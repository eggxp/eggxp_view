//---------------------------------------------------------------------------
#pragma hdrstop
#include "cryptclass.h"
#include "..\CommFunc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//------------------------------------------------------------------------------
int GetBufferLen(int SrcLen)
{
    int  ProcessLen;
    if (SrcLen <=8)
    {
      ProcessLen = 8;
    }
    else
    {
      ProcessLen = SrcLen/8 * 8 + 8; //补齐后8位
    }
    return ProcessLen;
}
//------------------------------------------------------------------------------
__fastcall WY_RSA::WY_RSA()
{
    memset(&m_KeyData,0,sizeof(m_KeyData));
    #ifdef SERVER_CRYPT_SIDE
    memset(&m_PrivateKey,0,sizeof(m_PrivateKey));
    #endif
}
//------------------------------------------------------------------------------
__fastcall WY_RSA::~WY_RSA()
{

}
//------------------------------------------------------------------------------
void WY_RSA::GetTruePublicKey(R_RSA_PUBLIC_KEY  * PublicKey)
{
    LoadPublicKeyData(EnKeyDataStr,KeyDataDecryptKey,&m_KeyData);
    CopyMemory(PublicKey,&m_KeyData.PublicKey,sizeof(R_RSA_PUBLIC_KEY));
    memset(&m_KeyData,0,sizeof(m_KeyData)); //取出后马上将m_keydata清空,防止keydata暴露
}
//------------------------------------------------------------------------------
void WY_RSA::GetTruePrivateKey(R_RSA_PRIVATE_KEY  * PrivateKey)
{
   #ifdef SERVER_CRYPT_SIDE
    CopyMemory(PrivateKey,&m_PrivateKey,sizeof(m_PrivateKey));
   #else
    memset(PrivateKey,0,sizeof(R_RSA_PRIVATE_KEY));
   #endif
}
//------------------------------------------------------------------------------
void WY_RSA::GetTrueRandomStruct(R_RANDOM_STRUCT  * RandomStruct)
{
    LoadPublicKeyData(EnKeyDataStr,KeyDataDecryptKey,&m_KeyData);
    CopyMemory(RandomStruct,&m_KeyData.RandomStruct,sizeof(R_RANDOM_STRUCT));
    memset(&m_KeyData,0,sizeof(m_KeyData)); //取出后马上将m_keydata清空,防止keydata暴露
}

//------------------------------------------------------------------------------
String __fastcall WY_RSA::PublicEncrypt(const String &Data)
{
     char OutBuf[MAX_TEMP_OUTPUT_BUFFER_LEN];
     R_RSA_PUBLIC_KEY  PublicKey;
     R_RANDOM_STRUCT   RandomStruct;
     GetTruePublicKey(&PublicKey);
     GetTrueRandomStruct(&RandomStruct);
     unsigned int  ResultLen = MAX_TEMP_OUTPUT_BUFFER_LEN;
     if (RSAPublicEncrypt(OutBuf,&ResultLen,Data.c_str(),Data.Length(),&PublicKey,&RandomStruct)==RSA_ID_OK)
     {
         return EncodeStr(String(OutBuf,ResultLen));
     }
     return "";
}
//------------------------------------------------------------------------------
String __fastcall WY_RSA::PublicDecrypt(const String &Data)
{
     char OutBuf[MAX_TEMP_OUTPUT_BUFFER_LEN];
     unsigned int  ResultLen = MAX_TEMP_OUTPUT_BUFFER_LEN;
     R_RSA_PUBLIC_KEY  PublicKey;
     GetTruePublicKey(&PublicKey);
     String DecStr = DecodeStr(Data);
     if (RSAPublicDecrypt(OutBuf,&ResultLen,DecStr.c_str(),DecStr.Length(),&PublicKey)==RSA_ID_OK)
     {
         return String(OutBuf,ResultLen);
     }
     return "";
}
//------------------------------------------------------------------------------
String __fastcall WY_RSA::PrivateEncrypt(const String &Data)
{
     #ifdef SERVER_CRYPT_SIDE
     char OutBuf[MAX_TEMP_OUTPUT_BUFFER_LEN];
     unsigned int  ResultLen = MAX_TEMP_OUTPUT_BUFFER_LEN;
     R_RSA_PRIVATE_KEY   PrivateKey;
     GetTruePrivateKey(&PrivateKey);
     if (RSAPrivateEncrypt(OutBuf,&ResultLen,Data.c_str(),Data.Length(),&PrivateKey)==RSA_ID_OK)
     {
         return EncodeStr(String(OutBuf,ResultLen));
     }
     #endif
     return "";
}
//------------------------------------------------------------------------------
String __fastcall WY_RSA::PrivateDecrypt(const String &Data)
{
      #ifdef SERVER_CRYPT_SIDE
     char OutBuf[MAX_TEMP_OUTPUT_BUFFER_LEN];
     unsigned int  ResultLen = MAX_TEMP_OUTPUT_BUFFER_LEN;
     R_RSA_PRIVATE_KEY   PrivateKey;
     GetTruePrivateKey(&PrivateKey);
     String DecStr = DecodeStr(Data);
     if (RSAPrivateDecrypt(OutBuf,&ResultLen,DecStr.c_str(),DecStr.Length(),&PrivateKey)==RSA_ID_OK)
     {
         return String(OutBuf,ResultLen);
     }
     #endif
     return "";
}
//------------------------------------------------------------------------------
void __fastcall WY_RSA::MakeKey(int Bit,DWORD RandValue1,DWORD RandValue2)
{
      #ifdef SERVER_CRYPT_SIDE
      unsigned char  KG_Buffer[8];
      R_RSA_PROTO_KEY RsaProto;
      RsaProto.bits = Bit;
      RsaProto.useFermat4 = 1;
      m_KeyData.EncryptType = 0;
      CopyMemory(&KG_Buffer[0],(char *)&RandValue1,4);
      CopyMemory(&KG_Buffer[4],(char *)&RandValue2,4);
      R_RandomUpdate(&m_KeyData.RandomStruct,KG_Buffer,sizeof(KG_Buffer));
      unsigned int bytesNeeded;
      R_GetRandomBytesNeeded(&bytesNeeded, &m_KeyData.RandomStruct);
      R_GeneratePEMKeys(&m_KeyData.PublicKey,&m_PrivateKey,&RsaProto,&m_KeyData.RandomStruct);
      #endif
}
//------------------------------------------------------------------------------
void   __fastcall WY_RSA::LoadPublicKeyData(const String &Data,const String  &EncryptKey,tagPublicKeyData * lpOutKeyData)
{
      int EncryptType = StrToIntDef(Data.SubString(Data.Length(),1),0);
      WY_CryptBase    *lpCryptClass = NewCryptClass(EncryptType);
      String KeyDataEncryptStr;
      String EnStr = Data;
      EnStr.Delete(Data.Length(),1);
      try
      {
        lpOutKeyData->EncryptType = EncryptType;
        if (lpCryptClass)
        {
           lpCryptClass->Init(EncryptKey);
           KeyDataEncryptStr = lpCryptClass->DecryptStr(EnStr);
        }
        else
        {
           KeyDataEncryptStr = EnStr;
        }
      }
      __finally
      {
         delete lpCryptClass;
      }
      int Len = KeyDataEncryptStr.Length();
      if (Len <=0 || KeyDataEncryptStr.Length() < sizeof(tagPublicKeyData))
      {
        memset(lpOutKeyData,0,sizeof(tagPublicKeyData));
        return;
      }
      CopyMemory(lpOutKeyData,KeyDataEncryptStr.c_str(),sizeof(tagPublicKeyData));
      #ifdef _DEBUG
      DumpString(String((char *)lpOutKeyData,sizeof(tagPublicKeyData)),"c:\\rsakeyload.dat");
      #endif
}
//------------------------------------------------------------------------------
WY_CryptBase * NewCryptClass(int Type)
{
    // 0=不加密,1=Des,2=Blowfish,3=BaseXorAdd,4=idea
    WY_CryptBase    *lpCryptClass=NULL;
    switch(Type)
    {
        case 1:
            lpCryptClass = new WY_Des;
            break;

        case 2:
            lpCryptClass = new WY_BlowFish;
            break;

        case 3:
            lpCryptClass = new WY_Xor;
            break;

        case 4:
            lpCryptClass = new WY_Idea;
            break;

        default: lpCryptClass=NULL;
    }
    return lpCryptClass;
}
//------------------------------------------------------------------------------
String __fastcall WY_RSA::SavePublicKeyData(int             EncryptType,
                                      const String    &EncryptKey)
{
      #ifdef SERVER_CRYPT_SIDE
      m_KeyData.EncryptType = EncryptType;
      #ifdef _DEBUG
      DumpString(String((char *)&m_KeyData,sizeof(m_KeyData)),"c:\\rsakey.dat");
      #endif
      WY_CryptBase    *lpCryptClass = NewCryptClass(EncryptType);
      String KeyDataEncryptStr;
      try
      {
        if (lpCryptClass)
        {
           lpCryptClass->Init(EncryptKey);
           KeyDataEncryptStr = lpCryptClass->EncryptStr(String((char *)&m_KeyData,sizeof(m_KeyData)));
        }
        else
        {
           KeyDataEncryptStr.SetLength(sizeof(m_KeyData));
           CopyMemory(KeyDataEncryptStr.c_str(),(char *)&m_KeyData,sizeof(m_KeyData));
        }
      }
      __finally
      {
         delete lpCryptClass;
      }
      KeyDataEncryptStr = KeyDataEncryptStr+ IntToStr(EncryptType);
      return KeyDataEncryptStr;
      #else
         return EncryptKey;
      #endif

}
//------------------------------------------------------------------------------
String __fastcall WY_RSA::SavePrivateKey()
{
    //保存私有key
    #ifdef SERVER_CRYPT_SIDE
    return EncodeStr(String((char *)&m_PrivateKey,sizeof(m_PrivateKey)));
    #else
    return "";
    #endif
}
//------------------------------------------------------------------------------
void   __fastcall WY_RSA::LoadPrivateKey(const String &PrivateKeyData)
{
   //读取私有Key
   #ifdef SERVER_CRYPT_SIDE
   String DecodeKeyData = DecodeStr(PrivateKeyData);
   if (DecodeKeyData.Length() < sizeof(m_PrivateKey))
   {
      return;
   }
   CopyMemory(&m_PrivateKey,DecodeKeyData.c_str(),sizeof(m_PrivateKey));
   #endif
}
//------------------------------------------------------------------------------
//WY_CryptBase ,各种加密类的基类，封装了各个加密类的基本接口,和公共函数
//---------------------------------------------------------------------------
__fastcall WY_CryptBase::WY_CryptBase()
{
     memset(DesBuf,0,sizeof(DesBuf));
}
//------------------------------------------------------------------------------
__fastcall WY_CryptBase::~WY_CryptBase()
{

}
//------------------------------------------------------------------------------
void WY_CryptBase::EncryptStream(TMemoryStream *SrcStream,TMemoryStream *DesStream)
{
     DesStream->Clear();
     DesStream->Size = SrcStream->Size-SrcStream->Position;
     EncryptBuf((char *)SrcStream->Memory+SrcStream->Position,SrcStream->Size-SrcStream->Position,(char *)DesStream->Memory);
}
//---------------------------------------------------------------------------
void WY_CryptBase::DecryptStream(TMemoryStream *SrcStream,TMemoryStream *DesStream)
{
     DesStream->Clear();
     DesStream->Size = SrcStream->Size-SrcStream->Position;
     DecryptBuf((char *)SrcStream->Memory+SrcStream->Position,SrcStream->Size-SrcStream->Position,(char *)DesStream->Memory);
}
//---------------------------------------------------------------------------
String WY_CryptBase::EncryptStr(const String &Buf)
{
    memset(DesBuf,0,sizeof(DesBuf));
    int EnLen = EncryptBuf(Buf.c_str(),Buf.Length(),DesBuf);
    return EncodeStr(String(DesBuf,EnLen));
}
//---------------------------------------------------------------------------
String WY_CryptBase::DecryptStr(const String &Buf)
{
    memset(DesBuf,0,sizeof(DesBuf));
    String DecodeString = DecodeStr(Buf);
    int EnLen = DecryptBuf(DecodeString.c_str(),DecodeString.Length(),DesBuf);
    return String(DesBuf,EnLen);
}
//WY_BlowFish  加密类
//---------------------------------------------------------------------------
__fastcall WY_BlowFish::WY_BlowFish()
{
     ctx = new BLOWFISH_CTX;
}
//---------------------------------------------------------------------------
__fastcall WY_BlowFish::~WY_BlowFish()
{
     delete  ctx;
}
//---------------------------------------------------------------------------
void WY_BlowFish::Init(String Key)
{
     Blowfish_Init(ctx,Key.c_str(),Key.Length()); //天堂2Key长度要加1
}
//---------------------------------------------------------------------------
int WY_BlowFish::EncryptBuf(char *SrcBuf,int SrcLen,char *DesBuf)
{
   int srcLen,DataPos=0,DesPos=0;
   DWORD L,R;
   int  ProcessLen;
   char ProcessBuffer[MAX_TEMP_OUTPUT_BUFFER_LEN];
   memset(ProcessBuffer,0,sizeof(ProcessBuffer));
   ProcessLen = GetBufferLen(SrcLen);
   CopyMemory(ProcessBuffer,SrcBuf,SrcLen);
   while (DataPos<ProcessLen)
   {
     L = ReadDWORD(ProcessBuffer,DataPos);
     R = ReadDWORD(ProcessBuffer,DataPos);
     Blowfish_Encrypt(ctx,&L,&R);
     WriteDWORD(DesBuf,DesPos,L);
     WriteDWORD(DesBuf,DesPos,R);
   }
   return DesPos;

}
//---------------------------------------------------------------------------
int WY_BlowFish::DecryptBuf(char *SrcBuf,int SrcLen,char *DesBuf)
{
   int srcLen,DataPos=0,DesPos=0;
   DWORD L,R;
   if (SrcLen % 8 !=0)   //输入数据错误
   {
      return 0;
   }
   while (DataPos<SrcLen)
   {
     L = ReadDWORD(SrcBuf,DataPos);
     R = ReadDWORD(SrcBuf,DataPos);
     Blowfish_Decrypt(ctx,&L,&R);
     WriteDWORD(DesBuf,DesPos,L);
     WriteDWORD(DesBuf,DesPos,R);
   }
   return DesPos;
}
//Des算法加密类
//------------------------------------------------------------------------------
void WY_Des::Init(String Key)
{
     m_Key = Key;
}
//------------------------------------------------------------------------------
int WY_Des::EncryptBuf(char    *SrcBuf,
                       int     SrcLen,
                       char    *DesBuf)
{
    int     ProcessLen;
    char    ProcessBuffer[MAX_TEMP_OUTPUT_BUFFER_LEN];
    memset(ProcessBuffer, 0, sizeof(ProcessBuffer));
    ProcessLen = GetBufferLen(SrcLen);
    CopyMemory(ProcessBuffer, SrcBuf, SrcLen);

    unsigned char   initVect[8];
    memcpy((char *)initVect, m_Key.c_str() + 8, 8);
    DES_CBCInit(&Context, m_Key.c_str(), initVect, IDEA_ENCRYPT);
    for(int k = 0; k < ProcessLen; k += 8)
    {
        DES_CBCUpdate(&Context,
                      &DesBuf[k],
                      (unsigned char *) &ProcessBuffer[k],
                      8);
    }

    return ProcessLen;
}
//------------------------------------------------------------------------------
int  WY_Des::DecryptBuf(char *SrcBuf,int SrcLen,char *DesBuf)
{
     if (SrcLen % 8 !=0)
     {
        return 0;
     }
     unsigned char   initVect[8];
     memcpy((char *)initVect, m_Key.c_str() + 8, 8);
     //加密一段内存数据,虚拟函数
     DES_CBCInit(&Context, m_Key.c_str(), initVect, IDEA_DECRYPT);
     for(int k=0; k<SrcLen; k+=8)
     {
        DES_CBCUpdate(&Context, &DesBuf[k],(unsigned char*)&SrcBuf[k],8);
     }
     return SrcLen;
}
//------------------------------------------------------------------------------
void WY_Idea::Init(String Key)
{
     m_Key =  Key;
}
//------------------------------------------------------------------------------
int  WY_Idea::EncryptBuf(char *SrcBuf,int SrcLen,char *DesBuf)
{
    //加密一段内存数据,虚拟函数
    int     ProcessLen;
    char    ProcessBuffer[MAX_TEMP_OUTPUT_BUFFER_LEN];
    memset(ProcessBuffer, 0, sizeof(ProcessBuffer));
    ProcessLen = GetBufferLen(SrcLen);
    CopyMemory(ProcessBuffer, SrcBuf, SrcLen);

    unsigned char   initVect[8];
    memcpy((char *)initVect, m_Key.c_str() + 8, 8);
    IDEA_KEY_SCHEDULE encrypt_ks, decrypt_ks;
    idea_set_encrypt_key(m_Key.c_str(),&encrypt_ks);
    idea_ecb_encrypt(SrcBuf, DesBuf, &encrypt_ks);
    idea_cbc_encrypt(SrcBuf, DesBuf, ProcessLen, &encrypt_ks, initVect, IDEA_ENCRYPT);
    return ProcessLen;
}
//------------------------------------------------------------------------------
int  WY_Idea::DecryptBuf(char *SrcBuf,int SrcLen,char *DesBuf)
{
     if (SrcLen % 8 !=0)
     {
        return 0;
     }
    unsigned char   initVect[8];
    memcpy((char *)initVect, m_Key.c_str() + 8,8);
    IDEA_KEY_SCHEDULE encrypt_ks, decrypt_ks;
    idea_set_encrypt_key(m_Key.c_str(), &encrypt_ks);
    idea_set_decrypt_key(&encrypt_ks, &decrypt_ks);
    idea_ecb_encrypt(SrcBuf, DesBuf, &decrypt_ks);
    idea_cbc_encrypt(SrcBuf, DesBuf, SrcLen, &decrypt_ks, initVect, IDEA_DECRYPT);
    return   SrcLen;
}
//------------------------------------------------------------------------------
void WY_Xor::Init(String Key)
{
   m_Key = Key;
}
//------------------------------------------------------------------------------
int  WY_Xor::EncryptBuf(char *SrcBuf,int SrcLen,char *DesBuf)
{
  //加密一段内存数据,虚拟函数,不变长度
  BaseXorAdd(SrcBuf,SrcLen,m_Key.c_str(),m_Key.Length());
  CopyMemory(DesBuf,SrcBuf,SrcLen);
  return SrcLen;
}
//------------------------------------------------------------------------------
int  WY_Xor::DecryptBuf(char *SrcBuf,int SrcLen,char *DesBuf)
{
  BaseXorSub(SrcBuf,SrcLen,m_Key.c_str(),m_Key.Length());
  CopyMemory(DesBuf,SrcBuf,SrcLen);
   return SrcLen;
}



