/** @defgroup CommFunc 常用扩展函数,基于VCL,只能用于BCB(CommFunc.h)
 *  @author  eggxp
 *  @version 1.0
 *  @date    2005.02.20
 *  @{
 */


//---------------------------------------------------------------------------
#ifndef CommFuncH
#define CommFuncH
#include <Classes.hpp>
#include <Windows.h>
#include <time.h>
#include <Graphics.hpp>

typedef __int64 int64;
typedef __int32 int32;
typedef short int16;
typedef char int8;
typedef unsigned __int64 uint64;
typedef unsigned __int32 uint32;
typedef WORD uint16;
typedef BYTE uint8;

typedef uint64 far           *LPUINT64;

/** 安全删除释放一个指针所对应的内存 */
#define  SAFE_DELETE(p)	 { if ( p ) { delete ( p );     ( p ) = NULL; } }
//---------------------------------------------------------------------------
typedef struct tagPosInfo
{
  DWORD X;
  DWORD Y;
  DWORD ReMapCode;
}
POSINFO,*PPOSINFO;
//---------------------------------------------------------------------------
typedef struct tagSearchWindowData
{
  DWORD  dwOwnerPID;
  LPCSTR strClassName;
  LPCSTR strWindowName;
  HWND   hWnd;
}SEARCHWINDOWDATA, *LPSEARCHWINDOWDATA;
/** @defgroup  String 字符串处理
 *  @{
 */
/** 格式化输出 \n
 *  printf格式化输出的AnsiString版本
 *  @param[in] Info      格式化字符串,具体可参见c库printf帮助
 *  @param[in] ...       变长参数
 *  @return 返回格式化后的字符串,AnsiString类型
  *  @note 如果格式化类型和实际传入类型不符，可能会引发VCL抛出异常，比如 %s对应SmallString
 *  @par 示例:
 *  @code
    String Info = FormatStr("你打死了: %s,获得EXP:%d",EName,Exp);
 *  @endcode
 
 *  @see ::FormatString
 *  @deprecated VCL AnsiString类中的sprintf成员函数有类似功能
 */

//#ifdef UNICODE
//#define	FormatStr	FormatStrW
//#else
//#define	FormatStr	FormatStrA
//#endif // !UNICODE
//
//String FormatStrW(wchar_t *Info, ...);
//String FormatStrA(char *Info, ...);

#define	FormatStr	FormatString

/** 格式化输出(String版) \n
 *  printf格式化输出的AnsiString版本
 *  @param[in] Info      格式化字符串,具体可参见c库printf帮助
 *  @param[in] ...       变长参数
 *  @return 返回格式化后的字符串,AnsiString类型
  *  @note 如果格式化类型和实际传入类型不符，可能会引发VCL抛出异常，比如 %s对应SmallString
 *  @par 示例:
 *  @code
	String FormatInfo = "你打死了: %s,获得EXP:%d";
	String Info = FormatString(FormatInfo,EName,Exp);
 *  @endcode

 *  @see ::FormatStr
 *  @deprecated VCL AnsiString类中的sprintf成员函数有类似功能
 */
String FormatString(String Info, ...); //格式化输出

/** 分割字符串 \n
 *  将一个字符串根据某个子串分割成字符串列表
 *  @param[in] SrcStr    源字符串,待分割的字符串
 *  @param[in] SplitChar 分割符,可以是多个字符
 *  @param[in] Str       输出字符串列表,保存分割后的结果
 *  @return 无返回值
 *  @note 分割好的字符串保存在TStrings中
 *  @par 示例:
 *  @code
    TStringList * OutputString = new TStringList;
	String SrcString = "徐,沈,申";
    SplitStr(SrcString,",",OutputString);
	//OutputString结果:
	//OutputString->String[0] == "徐"
	//OutputString->String[1] == "沈"
	//OutputString->String[2] == "申"
 *  @endcode
 *  @see 无
 *  @deprecated 无
 */
void SplitStr(AnsiString SrcStr,AnsiString SplitChar,TStrings *Str);
void SplitStrOld(AnsiString SrcStr,AnsiString SplitChar,TStrings *Str);


//String 		HexStrToBYTE(String Data);      //效率低下,弃用,仅仅为兼容旧代码而保留
int     	HexStrToBin(LPBYTE OutputBuf,String SrcData);//效率低下,弃用,仅仅为兼容旧代码而保留
AnsiString      HexStrToBinStr(String SrcData);

/** 16进制字符串转换成二进制数据 \n
 *  源字符串中间带空格 AB 90 DD -> AB90DD,汇编优化版
 *  @param[in] SrcText     //源缓冲区（0结尾字符串)
 *  @param[in] DesBuffer  目标缓冲区(二进制数据)
 *  @param[in] DesBufSize        目标缓冲区长度
 *  @param[in] HasSplitChar        是否带分隔字符
 *  @return 返回转换后的数据长度
 *  @note
 *  @par 示例:
 *  @code
	  String SrcText = "AB 90 DD";
	  char   DesBuffer[1024];
	  int BufferLen =  WY_HexToBin(SrcText.c_str(),DesBuffer,sizeof(DesBuffer));
	  //结果:
	  //BufferLen = 3
	  //DesBuffer[0] = 0xAB
	  //DesBuffer[1] = 0x90
	  //DesBuffer[2] = 0xDD
 *  @endcode
 *  @see WY_BinToHex
 *  @deprecated 无
 */
int __fastcall WY_HexToBin(char * SrcText, char * DesBuffer,int DesBufSize,bool HasSplitChar=true);

/** 二进制数据转换成16进制字符串 \n
 *  结果字符串中间分隔符可以设定 ,汇编优化版
 *  @param[in] DesText    目标缓冲区（0结尾字符串)
 *  @param[in] SrcBuffer  源缓冲区(二进制数据)
 *  @param[in] SrcBufSize        源缓冲区长度
 *  @param[in] SplitChar         //自定义分隔字符，0为不使用分隔符
 *  @return 无返回值
 *  @note
 *  @par 示例:
 *  @code
	  char   DesText[100];
	  memset(DesText,0,sizeof(DesText));
	  char   SrcBuffer[3]={0xAA,0xBB,0x10};
	  WY_BinToHex(DesText,SrcBuffer,sizeof(SrcBuffer),',');
	  ShowMessge(DesText);
	  //结果:
	   DesText = "AA,BB,10";
 *  @endcode
 *  @see WY_HexToBin
 *  @deprecated 无
 */
void __fastcall WY_BinToHex(char * DesText,const char * SrcBuffer,int SrcBufSize,const char SplitChar=' ');


/** 二进制数据转换成16进制字符串 \n
 *  包装,调用 WY_BinToHex函数，以便于返回String,易于使用
 *  @param[in] SrcBuffer    源缓冲区(二进制数据)
 *  @param[in] SrcLen        源缓冲区长度
 *  @return 无返回值
 *  @note  默认值是用' '作为分割符
 *  @par 示例:
 *  @code
	  char   SrcBuffer[3]={0xAA,0xBB,0x10};
	  String  DesText = BinToStr(SrcBuffer,sizeof(SrcBuffer));
	  ShowMessge(DesText);
	  //结果:
	   DesText = "AA,BB,10";
 *  @endcode
 *  @see WY_BinToHex
 *  @deprecated 无
 */
String  BinToStr(char* SrcBuffer, int SrcLen);

/** 将一个String里的内容保存到文件中 \n
 *  将String里的内容导出到指定文件
 *  @param[in] Data       String数据
 *  @param[in] FileName   文件名,必须包含完整路径,比如: c:\\test.dat
 *  @return 无返回值
 *  @note
 *  @par 示例:
 *  @code
	  char    SrcBuffer[3]={0xAA,0xBB,0x10};
	  DumpString(String(SrcBuffer),"c:\\test.dat");
	  //结果:
	   test.dat的内容是:  0xAA 0xBB 0x10
 *  @endcode
 *  @see WY_BinToHex
 *  @deprecated 无
 */
void  DumpString(String Data,String FileName);

/** 统计字符串中某子串的个数
 *
 *  @param[in] InStr     源字符串
 *  @param[in] SubStr    需要统计的字符串
 *  @return 被统计子串的个数
 *  @note   被统计子串是大小写敏感的
 *  @par 示例:
 *  @code
	  String SrcStr = "play you game,play,play,play";
	  int Count = CountChar(SrcStr,"play");
	  //结果:
	   Count = 4
 *  @endcode
 *  @see WY_BinToHex
 *  @deprecated 无
 */
int   CountChar(String InStr,String SubStr);

/** 分割字符串成一对数值 \n
 *  按","分割字符串为2个,并转换成数值
 *  @param[in] SrcStr        源字符串
 *  @param[in] LeftValue     分割后的左值
 *  @param[in] RightValue    分割后的右值
 *  @return  是否分割成功
 *  @note    分割符是","
 *  @par 示例:
 *  @code
	  String SrcStr = "111,222";
	  int Value1;
	  int Value2;
	  if (GetPairWWByStr(SrcStr,Value1,Value2))
	  {
		 ShowMessage(IntToStr(Value1+Value2));
	  }
	  //结果:
	   Value1 = 111;
	   VAlue2 = 222;
 *  @endcode
 *  @see GetPairWSByStr
 *  @deprecated 无
 */
bool GetPairWWByStr(String SrcStr,int &LeftValue,int &RightValue);

/** 分割字符串成一个数值,一个字符串 \n
 *  按","分割字符串为2个,并转换成一个数值,一个字符串
 *  @param[in] SrcStr        源字符串
 *  @param[in] LeftValue     分割后的左值(数值)
 *  @param[in] RightValue    分割后的右值(字符串)
 *  @return  是否分割成功
 *  @note    分割符是","
 *  @par 示例:
 *  @code
	  String SrcStr = "111,222";
	  int Value1;
	  String Value2;
	  if (GetPairWWByStr(SrcStr,Value1,Value2))
	  {
		 ShowMessage(IntToStr(Value1));
	  }
	  //结果:
	   Value1 = 111;
	   VAlue2 = "222";
 *  @endcode
 *  @see GetPairWWByStr
 *  @deprecated 无
 */
bool GetPairWSByStr(String SrcStr,int &LeftValue,String &RightValue);

/** 分割字符串成3个数值\n
 *  按","分割字符串为3个,并转换成3个数值
 *  @param[in] SrcStr        源字符串
 *  @param[in] Index     分割后的(数值1)
 *  @param[in] Value1    分割后的(数值2)
 *  @param[in] Value2   分割后的(数值3)
 *  @return  是否分割成功
 *  @note    分割符是","
 *  @par 示例:
 *  @code
	  String SrcStr = "111,222,333";
	  int Value1;
	  int Value2;
	  int Value3;
	  if (GetPairWWByStr(SrcStr,Value1,Value2,Value3))
	  {
		 ShowMessage(IntToStr(Value1));
	  }
	  //结果:
	   Value1 = 111;
	   VAlue2 = 222;
	   Value3 = 333;
 *  @endcode
 *  @see GetPairWWByStr
 *  @deprecated 无
 */
bool Get3ValueByStr(String SrcStr,int &Index,int &Value1,int &Value2);

/** 取出字符串中所有字母\n
 *  内部调用isalpha(c)实现
 *  @param[in] InStr      源字符串
 *  @return  由字母所组成的子串
 *  @note    非字母字符全部去除
 *  @par 示例:
 *  @code
	  String SrcStr = "22 King Of Fighter 99";
	  String SubStr =  GetAlpha(SrcStr);
	  //结果:
	  //SubStr = "KingOfFighter";
 *  @endcode
 *  @see GetDigit
 *  @deprecated 无
 */
String GetAlpha(String InStr);
/** 取出字符串中所有数字\n
 *  内部调用isdigit(c)实现
 *  @param[in] InStr      源字符串
 *  @return  由字母所组成的子串
 *  @note    非数值字符全部去除
 *  @par 示例:
 *  @code
	  String SrcStr = "22 King Of Fighter 99";
	  String SubStr =  GetDigit(SrcStr);
	  //结果:
	  //SubStr = "2299";
 *  @endcode
 *  @see GetAlpha
 *  @deprecated 无
 */
String GetDigit(String InStr);

/** 取出字符串中所有数字\n
 *  并且去除无效的0
 *  @param[in] InStr      源字符串
 *  @return  由合法数值组成的子串
 *  @note    非数值字符全部去除,无效0字符全部去除
 *  @par 示例:
 *  @code
	  String SrcStr = "JY00088888";
	  String SubStr =  GetTrueNumber(SrcStr);
	  //结果:
	  //SubStr = "88888";
 *  @endcode
 *  @see GetDigit
 *  @deprecated 无
 */
String GetTrueNumber(String InStr);

/** 从一个字符串开始读取到某字符串结束\n
 *  返回子串
 *  @param[in] SrcString      源字符串
 *  @param[in] TokenChar      停止字符串
 *  @return  从源串第一个字符开始到停止字符串之间的子串
 *  @note
 *  @par 示例:
 *  @code
	  String SrcStr = "JJ Kill You";
	  String SubStr =  ReadToken(SrcStr," ");
	  //结果:
	  //SubStr = "JJ ";
 *  @endcode
 *  @see GetDigit
 *  @deprecated 无
 */
String ReadToken(String &SrcString,String TokenChar);

/** 取出一个字符串在某个字符左边的字符串
 *  @param[in] SrcString      源字符串
 *  @param[in] TokenStr      分割字符串
 *  @return  分割符左边的字符串
 *  @note    分割符为","
 *  @par 示例:
 *  @code
	  String SrcStr = "JJ,Kill";
	  String SubStr =  LeftString(SrcStr);
	  //结果:
	  //SubStr = "JJ";
 *  @endcode
 *  @see RightString
 *  @deprecated 无
 */
String LeftString(const String &SrcString,String TokenStr);

/** 取出一个字符串在某个字符右边的字符串
 *  @param[in] SrcString      源字符串
 *  @param[in] TokenStr       分割字符串
 *  @return  分割符右边的字符串
 *  @note    分割符为","
 *  @par 示例:
 *  @code
	  String SrcStr = "JJ,Kill";
	  String SubStr =  RightString(SrcStr);
	  //结果:
	  //SubStr = "Kill";
 *  @endcode
 *  @see LeftString
 *  @deprecated 无
 */
String RightString(const String &SrcString,String TokenStr);

/** @}*/ // 字符串处理

/** @defgroup OSExpand Windows操作系统功能函数
 *  @{
 */
/** 检查OS字符集是否有简体字库 \n
 *  
 *  @return 如果没有,返回False,表示以简体语言为主要语言的程序无法在此系统上运行 , 如果有简体字库,返回True
 *  @note   如果没有简体字符集字库,那么即使使用转码函数，也无法保证简体程序可以在繁体上完全正常运行
 *  @par 示例:
 *  @code
    if (!CheckOS_Font())
    {
       ShowMessage("your windows can't run this application!!");
       
    }
 *  @endcode
 */
bool   CheckOS_Font();

/** @}*/ // Windows操作系统功能函数


/** @defgroup Process 进程信息,内存读写
 *  @{
 */
 /** 读取某个窗口进程的某段内存数据\n
 *
 *  @param[in] aClassName    目标进程窗口类名,只要是此进程所属的窗口，就可以作为参数
*  @param[in] BaseAddr       要读取的进程内存地址
*  @param[in] Len            要读取的长度
*  @param[in] lpBuf          存放结果的缓冲区指针
 *  @return 如果读取失败,返回False,如果读取成功,返回True
 *  @note   读取失败的原因可能是:窗口未找到,窗口所对应的进程id未找到,ReadProcessMemory函数失败
 *  @par 示例:
 *  @code
	 BYTE lpBuffer[8192];
	if (ReadMemory("TForm1",0x4123ab9,100,lpBuffer))
	{
	   ShowMessage(FormatStr("进程的0x4123ab9内存地址处的数据为:%s",BinToStr((char *)lpBuffer,100)));
	}
	else
	{
	   ShowMessage("读取失败");
	}
 *  @endcode
 */
bool ReadMemory(String aClassName, DWORD BaseAddr, DWORD Len, LPBYTE lpBuf);
 /** 写入某个窗口进程的某段内存数据\n
 *  
 *  @param[in] ClassName    目标进程窗口类名,只要是此进程所属的窗口，就可以作为参数
*  @param[in] BaseAddr       要写入的进程内存地址
*  @param[in] Len            要写入的长度
*  @param[in] Buf          存放写入内容的缓冲区指针
 *  @return 如果写入失败,返回False,如果读取成功,返回True
 *  @note   读取失败的原因可能是:进程ID或地址无效,写入权限不具备
 *  @par 示例:
 *  @code
	 BYTE lpBuffer[8192];
	if (D_WriteMemory("TForm1",0x4123ab9,100,lpBuffer))
	{
	   ShowMessage(FormatStr("进程的0x4123ab9内存地址处的数据为:%s",BinToStr((char *)lpBuffer,100)));
	}
	else
	{
	   ShowMessage("写入内存失败");
	}
 *  @endcode
 */
bool WriteMemory(String ClassName,DWORD BaseAddr, DWORD Len, LPBYTE Buf);

 /** 读取某个进程的某段内存数据\n
 *  
 *  @param[in] ProcessID    目标进程ID
*  @param[in] BaseAddr       要读取的进程内存地址
*  @param[in] Len            要读取的长度
*  @param[in] lpBuf          存放结果的缓冲区指针
 *  @return 如果读取失败,返回False,如果读取成功,返回True
 *  @note   读取失败的原因可能是:进程ID或地址无效,ReadProcessMemory函数失败
 *  @par 示例:
 *  @code
	 BYTE lpBuffer[8192];
	if (ReadMemory(GetCurrentProcessID(),0x4123ab9,100,lpBuffer))
	{
	   ShowMessage(FormatStr("进程的0x4123ab9内存地址处的数据为:%s",BinToStr((char *)lpBuffer,100)));
	}
	else
	{
	   ShowMessage("读取失败");
	}
 *  @endcode
 */
bool D_ReadMemory(DWORD ProcessID,DWORD BaseAddr,DWORD Len, LPBYTE lpBuf);
 /** 写入某个进程的某段内存数据\n
 *
 *  @param[in] ProcessID    目标进程ID
*  @param[in] BaseAddr       要写入的进程内存地址
*  @param[in] Len            要写入的长度
*  @param[in] Buf          存放写入内容的缓冲区指针
 *  @return 如果写入失败,返回False,如果读取成功,返回True
 *  @note   读取失败的原因可能是:进程ID或地址无效,写入权限不具备
 *  @par 示例:
 *  @code
	 BYTE lpBuffer[8192];
	if (D_WriteMemory(GetCurrentProcessID(),0x4123ab9,100,lpBuffer))
	{
	   ShowMessage(FormatStr("进程的0x4123ab9内存地址处的数据为:%s",BinToStr((char *)lpBuffer,100)));
	}
	else
	{
	   ShowMessage("写入内存失败");
	}
 *  @endcode
 */
bool D_WriteMemory(DWORD ProcessID,DWORD BaseAddr, DWORD Len, LPBYTE Buf);


String GetProcessName();
DWORD MyWinExeC(const String &Cmdline,String DirName,int Visibility= SW_SHOW);
void  PopUpWindow(HWND WinHwnd);  //将窗口显示到最前端
/** @}*/ // 进程信息,内存读写

/**  @defgroup Number 进制转换,数值处理
 *  @{
 */

 /** 将一串62进制字符串转换成10进制数值
 *  @param[in] s          62进制数字符串 范围 ASC '0' - 'Z'
 *  @return 返回62进制表示字符串所对应的10进制数值
 *  @note   某些场合可能会用62进制表示,比如魔力宝贝和石器时代系列的封包
 *  @par 示例:
 *  @see ::c_10To62
 *  @code
	 int Value =  c_62To10("azd");
	 ShowMessage(FormatStr("62进制数 azd 的10进制数值为:%d",Value));
 *  @endcode
 */
int c_62To10(String s);

 /** 将10进制数值转换成一串62进制字符串
 *  @param[in] Value    10进制数值
 *  @return 返回 10进制数值所对应的62进制字符串
 *  @note   某些场合可能会用62进制表示,比如魔力宝贝和石器时代系列的封包
 *  @par 示例:
 *  @see ::c_62To10
 *  @code
	 String Str_62 =  c_10To62(1000);
	 ShowMessage(FormatStr("10进制数值1000的62进制是:%s",Str_62));
 *  @endcode
 */
String c_10To62(int Value);
float  NumberToPercent(int Number1,int Number2);
/** @}*/  // 进制转换,数值处理


//数组处理

void ReadBuf(LPVOID Buf,int &DataPos,LPVOID DesBuf,int Len);
BYTE ReadBYTE(LPBYTE Buf,int &DataPos);
BYTE ReadBit(BYTE * data, int maxLength, int index);
WORD ReadWORD(LPBYTE Buf,int &DataPos);
DWORD ReadDWORD(LPBYTE Buf,int &DataPos);
uint64 ReadUINT64(LPBYTE Buf,int &DataPos);
double ReadDouble(LPBYTE Buf,int &DataPos);
float ReadFloat(LPBYTE Buf,int &DataPos);


void WriteBuf(LPVOID Buf,int &DataPos,LPVOID SrcBuf,int Len);
void WriteBYTE(LPBYTE Buf,int &DataPos,BYTE Value);
void WriteBit(BYTE * data, int maxLength, int index, int value);
void WriteWORD(LPBYTE Buf,int &DataPos,WORD Value);
void WriteDWORD(LPBYTE Buf,int &DataPos,DWORD Value);
void WriteUINT64(LPBYTE Buf,int &DataPos,uint64 Value);
void WriteFloat(LPBYTE Buf,int &DataPos,float Value);
void WriteDouble(LPBYTE Buf,int &DataPos,double Value);
void WriteWideString(char *buf,int &DataPos,String &Text);
// motolora
void MotoReadBuf(LPVOID Buf,int &DataPos,LPVOID DesBuf,int Len);
BYTE MotoReadBYTE(LPBYTE Buf,int &DataPos);
WORD MotoReadWORD(LPBYTE Buf,int &DataPos);
DWORD MotoReadDWORD(LPBYTE Buf,int &DataPos);
double MotoReadDouble(LPBYTE Buf,int &DataPos);
float MotoReadFloat(LPBYTE Buf,int &DataPos);

void MotoWriteBuf(LPVOID Buf,int &DataPos,LPVOID SrcBuf,int Len);
void MotoWriteBYTE(LPBYTE Buf,int &DataPos,BYTE Value);
void MotoWriteWORD(LPBYTE Buf,int &DataPos,WORD Value);
void MotoWriteDWORD(LPBYTE Buf,int &DataPos,DWORD Value);
void MotoWriteFloat(LPBYTE Buf,int &DataPos,float Value);
void MotoWriteDouble(LPBYTE Buf,int &DataPos,double Value);



int  FindWORD(LPBYTE cData,int MaxLen,WORD Value);
int  FindDWORD(LPBYTE cData,int MaxLen,DWORD Value);
//简单算法
int  MakeLineStep(int CurX,int CurY,int DesX,int DesY,int Step,TList *WalkList);  //实现得不好,仅仅用于旧代码兼容,不推荐新代码使用
int  CalcPosDis(int CurX,int CurY,int DesX,int DesY);
void RotatePosByDis(int SrcX, int SrcY,int Dis,TPoint *DesPos, float Angle);
void RotatePos(int ZeroX,int ZeroY,int SrcX, int SrcY, TPoint *DesPos, float Angle);
int  GetAngle( int x1 , int  y1 , int x2 , int y2 );
int  GetReverseAngle(int OrgAngle);

//时间日期处理
TDateTime Unix_timeToPc_time(time_t t,bool UTC);

//文件,目录操作
int GetFileList(const String &Path,const String &Ext,TStrings *ResultList);
int GetFileList(const String &DirName,const String &Ext,TStrings *ResultList,bool SubDir);
int GetFileList(const String &DirName,const String &Ext,const String &TrueExt,TStrings *ResultList,bool SubDir);
String GetSysDir();
String EnvironmentPath(String PathName);
String GetCurDir();
void  ZeroTextFile(String FileName);
int GetFileSize(String sFileName);
DWORD GetFileCRC(String FileName);
int   GetLogicalDrive(TStrings *Drivers);
//调试信息
void ShowDebugInfo(String Info);
HWND __fastcall SearchWindow(DWORD ProcessId, LPCSTR strClassName, LPCSTR strWindowName);

//网络
int   GetLocalIP(TStrings * IPList);
bool  IsLocalIP(String IP);

//加密
int  WINAPI fnEncode6BitBufA(unsigned char *pszSrc, char *pszDest, int nSrcLen, int nDestLen);
int  WINAPI fnDecode6BitBufA(char *pszSrc, char *pszDest, int nDestLen);
String EncodeStr(String Src);
String DecodeStr(String Src);
DWORD _stdcall GetCrc32(DWORD crc, LPBYTE buf, UINT len);

//系统控制
void ShutDown();
void ReBoot();
bool IsWin2k();
bool ShutDown2K(UINT Flag);
String GetEXEVersion(const String &ExeNameStr);
//控件

//图像
TColor RGB2Color(BYTE R,BYTE G,BYTE B);
void   DrawShadeBar(TCanvas * DrawCanvas,int ClientWidth,int ClientHeight,bool VerticalDraw=false);      //画渐变色到一个TCanvas


bool	ProcessExists(DWORD processID);
TDateTime TTimeToDateTime(const time_t t);
//---------------------------------------------------------------------------

uint64 Uint64Pow(uint64 num, int val);
uint64 StrToUint64Def(String str, int def);
String ReplaceStr(String input, String from, String to);
bool ForceRemoveDir(String SourceDir);

double GetNowTick();
#endif


/** @}*/ // 常用扩展函数

