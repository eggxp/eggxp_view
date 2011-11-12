/*
一组通用函数,以加/解密为主,提供了Des和简单的Xor Add加密解密算法
作者:游勇鹏
最后更新日期: 2004.07.01
*/
//---------------------------------------------------------------------------
#ifndef GenericFuncH
#define GenericFuncH

#define SUCCESS         1
#define DESDECRY        0x0001
#define DESENCRY        0x0002
//---------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

int des(BYTE *data, BYTE *key,int readlen);
/*
参数:
1.存放待加密明文的内存指针(长度为readlen,可能经过填充;
2.存放用户输入的密钥内存的指针
3.待加密明文的长度(8字节的倍数)
功能:
生成加密密钥,把待加密的明文数据分割成64位的块,逐块完成16次迭代加密,密文存放在data所指向的内存中.
*/

int Ddes(BYTE *data,BYTE *key,int readlen);
/*
参数:
1.存放待解密文的内存指针(长度为readlen,可能经过填充;
2.存放用户输入的密钥内存的指针
3.待解密文的长度( 8字节的倍数)
功能:
生成解密密钥,把待解密文分割成64位的块,逐块完成16次迭代解密,解密后的明文存放在data所指向的内存中.
*/

int des3(BYTE *data, BYTE *key,DWORD n ,DWORD readlen);
/*
参数:
1.存放待加密明文的内存指针(长度为readlen,可能经过填充;
2.存放用户输入的密钥内存的指针
3.用户指定进行多少层加密
4.待加密明文的长度(8字节的倍数)
功能:
生成加密密钥,把待加密的明文分割成64位的块,把第i-1层加密后的密文作为第i层加密的明文输入,根据用户指定的加密层数进行n层加密,最终生成的密文存放在data所指向的内存中.
说明:
用户仅仅输入一条密钥,所有的加密密钥都是由这条密钥生成.
*/

int Ddes3(BYTE *data,BYTE *key,DWORD n ,DWORD readlen);
/*
参数:
1.存放待解密文的内存指针(长度为readlen,可能经过填充;
2.存放用户输入的密钥内存的指针
3.用户指定进行多少层解密
4.待解密文的长度(8字节的倍数)
功能:
生成解密密钥,把待解密文分割成64位的块,把第i-1层解密后的"明文"作为第i层解密的密文输入,根据用户指定的解密层数进行n层解密,最终生成的明文存放在data所指向的内存中.
说明:
用户仅仅输入一条密钥,所有的解密密钥都是由这条密钥生成.
*/

int desN(BYTE *data, BYTE **key, DWORD n_key,DWORD readlen);
/*
参数:
1.存放待加密明文的内存指针(长度为readlen,可能经过填充;
2.存放用户输入的密钥内存的指针
3.用户指定了多少条密钥
4.待加密明文的长度(8字节的倍数)
功能:
生成加密密钥,把待加密的明文分割成64位的块,把第i-1层加密后的密文作为第i层加密的明文输入,根据用户指定的加密层数进行n层加密,最终生成的密文存放在data所指向的内存中.
说明:
这里用户通过输入的密钥条数决定加密的层数,每轮16次迭代加密所使用的加密密钥是由用户自定的对应密钥生成.
*/

int DdesN(BYTE *data, BYTE **key, DWORD n_key,DWORD readlen);
/*
参数:
1.存放待解密文的内存指针(长度为readlen,可能经过填充;
2.存放用户输入的密钥内存的指针
3.用户指定了多少条密钥
4.待解密文的长度(8字节的倍数)
功能:
生成解密密钥,把待解密文分割成64位的块,把第i-1层解密后的”明文”作为第i层解密的密文输入,根据用户指定的解密层数进行n层解密,最终生成的明文存放在data所指向的内存中.
说明:
这里用户通过输入的密钥条数决定解密的层数,每轮16次迭代加密所使用的解密密钥是由用户自定的对应密钥生成
*/

void Xor_Add(LPSTR szBuffer, int ulFileLen, LPSTR szPassword, int iPasswordLen);
// 或与并累加加密
void Xor_Sub(LPSTR szBuffer, int ulFileLen, LPSTR szPassword, int iPasswordLen);
// 或与并累加解密

BOOL BrowseFolder(HWND hParent, LPCTSTR lpTitle, LPTSTR DirName);
// 浏览目录
BOOL DirExists(LPSTR lpPath);
// 目录是否存在

extern DWORD iRandSeed;
DWORD __fastcall MyRandInt(DWORD i);

#ifdef __cplusplus
}
#endif //__cplusplus
//---------------------------------------------------------------------------
#endif
