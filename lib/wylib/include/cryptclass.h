//---------------------------------------------------------------------------
//网游加密库封装
//------------------------------------------------------------------------------
#ifndef cryptclassH
#define cryptclassH

#include <vcl.h>
#include "CryptoLib.h"
//------------------------------------------------------------------------------
//注意!!!!!!!!!!!!!!!
//SERVER_CRYPT_SIDE    //此宏生效,表示服务器端编码,屏蔽后表示客户端(将会去除所有关于私钥的代码)
//建议设定在project的option,项目包含选项
//------------------------------------------------------------------------------
#define MAX_TEMP_OUTPUT_BUFFER_LEN 1024 * 32

struct tagPublicKeyData //KeyData保存结构
{
   int EncryptType;
   R_RSA_PUBLIC_KEY  PublicKey;
   R_RANDOM_STRUCT   RandomStruct;
};

//各种加密解密算法的基类,RSA除外
class WY_CryptBase
{
private:
  char DesBuf[MAX_TEMP_OUTPUT_BUFFER_LEN];
protected:

public:
  __fastcall WY_CryptBase();
  virtual __fastcall ~WY_CryptBase();
  virtual void Init(String Key)=0;
  virtual int  EncryptBuf(char *SrcBuf,int SrcLen,char *DesBuf)=0;  //加密一段内存数据,虚拟函数
  virtual int  DecryptBuf(char *SrcBuf,int SrcLen,char *DesBuf)=0;  //解密一段内存数据,虚拟函数
  virtual void EncryptStream(TMemoryStream *SrcStream,TMemoryStream *DesStream);
  virtual void DecryptStream(TMemoryStream *SrcStream,TMemoryStream *DesStream);
  virtual String EncryptStr(const String &Buf);
  virtual String DecryptStr(const String &Buf);
};

//封装RSA算法
//使用过程:
//一. RSA Key生成
//1.使用 MakeKey 成员函数, 生成公钥和私钥数据,保存在m_KeyData
//2.使用 SaveKeyData 成员函数,保存公钥数据,并用加密算法加密，用base16保存成字符串,分发到客户端
//3.使用 SavePrivateKey 成员函数,保存私钥数据,用base16保存成字符串,分发到服务器端
//二. 客户端使用过程
//1. 调用SetKeyDataDecryptKey设置 解密publickey数据算法需要的Key(自定义)
//2.调用LoadEnKeyData设置 加密后的publickey数据
//3.调用PublicEncrypt函数可以进行公钥加密,用来加密发送给服务器端的数据
//4.调用PublicDecrypt函数可以进行公钥解密,用来解密从服务器端接收的数据

//三.服务器端使用过程
//1. 调用 LoadPrivateKey读取私有Key
//2. 调用 PrivateEncrypt加密数据，发送给客户端
//3. 调用 PrivateDecrypt,解密客户端发来的数据
class WY_RSA
{
private:
   tagPublicKeyData m_KeyData;
   #ifdef SERVER_CRYPT_SIDE
   R_RSA_PRIVATE_KEY m_PrivateKey;    //私有Key另外保存
   #endif
   String        EnKeyDataStr; //加密状态的KeyData数据
   String        KeyDataDecryptKey;
protected:
  virtual void GetTruePublicKey(R_RSA_PUBLIC_KEY  * PublicKey);
  virtual void GetTruePrivateKey(R_RSA_PRIVATE_KEY  * PrivateKey);
  virtual void GetTrueRandomStruct(R_RANDOM_STRUCT  * RandomStruct);
  virtual DWORD  GetDataBlockLen(R_RSA_PRIVATE_KEY  * PrivateKey);
  virtual DWORD  GetDataBlockLen(R_RSA_PUBLIC_KEY  * PubliceKey);
public:
  __fastcall WY_RSA();
  __fastcall ~WY_RSA();
  virtual void __fastcall MakeKey(int Bit,DWORD RandValue1,DWORD RandValue2);
  virtual String __fastcall PublicEncrypt(const String &Data); //公钥加密
  virtual String __fastcall PublicDecrypt(const String &Data); //公钥解密
  virtual String __fastcall PrivateEncrypt(const String &Data);  //私钥加密
  virtual String __fastcall PrivateDecrypt(const String &Data);  //私钥解密
  virtual void __fastcall   SetKeyDataDecryptKey(const String &Key){KeyDataDecryptKey = Key;} //设定解密还原RSA Key数据的密钥
  virtual void __fastcall   LoadEnKeyData(const String &Data){EnKeyDataStr=Data;} //读取加载key数据,按加密后状态保存
  virtual void   __fastcall LoadPublicKeyData(const String &Data,const String &EncryptKey,tagPublicKeyData * lpOutKeyData); //从加密状态的String读取Key数据
  virtual String __fastcall SavePublicKeyData(int EncryptType,const String &EncryptKey); //保存Key数据到String 0=不加密,1=Des,2=Blowfish,3=BaseXorAdd,4=idea
  virtual String __fastcall SavePrivateKey(); //保存私有key
  virtual void   __fastcall LoadPrivateKey(const String &PrivateKeyData); //读取私有Key
};


//封装Des算法的类
class WY_Des:public  WY_CryptBase
{
private:
   DES_CBC_CTX Context;
protected:
  String m_Key;
public:
  __fastcall WY_Des(){memset(&Context,0,sizeof(DES_CBC_CTX));}
  __fastcall ~WY_Des(){;}
  virtual void Init(String Key);
  virtual int  EncryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);  //加密一段内存数据,虚拟函数
  virtual int  DecryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);
};
//封装BlowFish算法的类
class WY_BlowFish:public  WY_CryptBase
{
private:
   BLOWFISH_CTX *ctx;

protected:

public:
  __fastcall WY_BlowFish();
  __fastcall ~WY_BlowFish();
  virtual void Init(String Key);
  virtual int  EncryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);  //加密一段内存数据,虚拟函数
  virtual int  DecryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);
};

//封装Idea算法的类
class WY_Idea:public  WY_CryptBase
{
private:
   String m_Key;
protected:

public:
  __fastcall WY_Idea(){;}
  __fastcall ~WY_Idea(){;}
  virtual void Init(String Key);
  virtual int  EncryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);  //加密一段内存数据,虚拟函数
  virtual int  DecryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);

};
//封装xoradd算法的类
class WY_Xor:public  WY_CryptBase
{
private:

protected:
  String m_Key;
public:
  __fastcall WY_Xor(){;}
  __fastcall ~WY_Xor(){;}
  virtual void Init(String Key);
  virtual int  EncryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);  //加密一段内存数据,虚拟函数
  virtual int  DecryptBuf(char *SrcBuf,int SrcLen,char *DesBuf);
};

WY_CryptBase * NewCryptClass(int Type);
//---------------------------------------------------------------------------
#endif
