//---------------------------------------------------------------------------

#ifndef applangH
#define applangH
#include <ActnList.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <IniFiles.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit
//子类负责自动转换项目语言
//自动转换程序中的 VCL控件。
//1. 创建  TAppLang对象
//2. 调用TAppLang->BindApplication(Application); 绑定项目对象TApplication
//3.若有控件不想自动转换，请将此控件的tag属性设置成255,则会忽略此控件
//4.若有窗口不想自动转换标题,请将此窗口的tag属性设置成254
//4.调用SaveToIni()函数则会将Application所有的窗口保存到 项目目录\lang.ini
//5.将lang.ini转换成对应的语言字符,另外保存,比如台湾版本，使用langtw.ini
//6.程序初始化的时候,使用LoadFromIni(INI文件名)初始化语言
//7.运行中也可以动态调用 LoadFromIni(INI文件名)切换语言版本
//8.记得把ini里面的字符集和字体更改成对应的语言  CHARSET=136
//                 								 Font=灿砰
//自动转换程序中的静态字符串
//1.定义语言管理宏
//2.输出字符 _DT("测试字符串")
//3.编译完之后使用applang.exe提取所有字符串，并翻译成对应的版本 ,保存成langtw.txt(台湾)

/*  if (Screen->Fonts->IndexOf("MingLu")>=0)
  {
	 ConvForm->Font->Name = "MingLu";
  }
  else
  {
     ConvForm->Font->Name = L"灿砰";    //细明体
  }
  ConvForm->Font->Size = 9;
  ConvForm->Font->Charset = CHINESEBIG5_CHARSET;   */

//GB2312_CHARSET		134	Simplified Chinese characters (mainland china).
//CHINESEBIG5_CHARSET	136	Traditional Chinese characters (Taiwanese).
//DEFAULT_CHARSET		1	Font is chosen based solely on Name and Size. If the described font is not available on the system, Windows will substitute another font.
#define MSG_CREATE_NEW_WINDOWS   WM_USER+5551


class TAppLang
{
private:
   TApplication  * OwnApplication;
   Inifiles::THashedStringList*  LocalStrIndex;
   String LastIniFile;
   bool				IsNullChar(String Text);
   TFontCharset		CharSet;
   String			FontName;
   bool				SaveFormCaption; //是否保存窗口标题
	void __fastcall OnMessage(tagMSG &Msg, bool &Handled);
	TForm *         FindForm(HWND FormHWND);
protected:
   void __fastcall SaveTComboBox(TMemIniFile * IniFile,String SecName,TComboBox * tagObj);
   void __fastcall LoadTComboBox(TMemIniFile * IniFile,String SecName,TComboBox * tagObj);
   void __fastcall SaveTListBox(TMemIniFile * IniFile,String SecName,TListBox * tagObj);
   void __fastcall LoadTListBox(TMemIniFile * IniFile,String SecName,TListBox * tagObj);
   void __fastcall SaveTNotebook(TMemIniFile * IniFile,String SecName,TNotebook * tagObj);
   void __fastcall LoadTNotebook(TMemIniFile * IniFile,String SecName,TNotebook * tagObj);
   void __fastcall SaveTListView(TMemIniFile * IniFile,String SecName,TListView * tagObj);
   void __fastcall LoadTListView(TMemIniFile * IniFile,String SecName,TListView * tagObj);
   void __fastcall SaveTAction(TMemIniFile * IniFile,String SecName,TAction * tagObj);   //特殊处理TAction
   void __fastcall LoadTAction(TMemIniFile * IniFile,String SecName,TAction * tagObj);
   void __fastcall SaveTMenuItem(TMemIniFile * IniFile,String SecName,TMenuItem * tagObj);   //特殊处理TMenuItem
   void __fastcall LoadTMenuItem(TMemIniFile * IniFile,String SecName,TMenuItem * tagObj);
   void __fastcall SaveTControl(TMemIniFile * IniFile,String SecName,TControl * tagObj);   //处理TControl
   void __fastcall LoadTControl(TMemIniFile * IniFile,String SecName,TControl * tagObj);
   void __fastcall SaveForm(TMemIniFile * IniFile,TForm * tagForm);
   void __fastcall LoadForm(TMemIniFile * IniFile,TForm * tagForm);
public:
	TAppLang();
	~TAppLang();
	void __fastcall SaveToIni();
	bool __fastcall LoadFromIni(String FileName);
	String _stdcall ShowText(DWORD Flag1, DWORD Flag2, char * Text);
	String _stdcall ShowTextArray(DWORD dwFlag1, DWORD dwFlag2, LPVOID *pStr, INT nSizeOfArray, INT nIndex);
	void			BindApplication(TApplication  * _OwnApplication);
};

//使用接口
TAppLang * AppLangPtr();
#define DT_FLAG1   0x11223344
#define DT_FLAG2   0x55667788
#define DT_FLAG3  0x99AABBCC
#define _DT(s)    					  AppLangPtr()->ShowText(DT_FLAG1,DT_FLAG2,s)
#define _TEXT_DT_ARRAYD(s, i)         AppLangPtr()->ShowTextArray(DT_FLAG1, DT_FLAG3, (LPVOID *)s, sizeof(s) / sizeof(char*), i)
#define _TEXT_DT_ARRAYP(s, i)         AppLangPtr()->ShowTextArray(DT_FLAG1, DT_FLAG3, (LPVOID *)s, -1, i)
#define _TEXT_DT_ARRAYPU(s, l, i)     AppLangPtr()->ShowTextArray(DT_FLAG1, DT_FLAG3, (LPVOID *)s, l, i)

//---------------------------------------------------------------------------
#endif
