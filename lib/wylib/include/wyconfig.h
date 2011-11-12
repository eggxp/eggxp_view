//---------------------------------------------------------------------------

#ifndef wyconfigH
#define wyconfigH
#include <vcl.h>
#include "amap.h"
#include "cspin.h"
#include <IniFiles.hpp>
//用于保存和读取用户设置
//保存模式 默认值,控件的Tag
enum ValueSaveType{vsDefault,vsTag};
//---------------------------------------------------------------------------
struct tagValueRecord
{
    TComponent *GUIComponent;
	Variant    Value;
    bool       GUI2Value();    //从GUI控件读取数值
    bool       Value2GUI();    //刷新GUI控件上显示的数值
    bool       WriteToINI(TCustomIniFile *lpIniFile,const String &SecName);
    bool       ReadFromINI(TCustomIniFile *lpIniFile,const String &SecName);
};
//---------------------------------------------------------------------------
class TConfig
{
private:
  AIndexList<tagValueRecord> * m_lpCommonConfig;     //使用Hash表以加快索引速度
protected:
  String m_RecordName;
public:
  __fastcall TConfig();
  virtual __fastcall ~TConfig();
  void __fastcall SetRecordName(const String &RecordName);    //设置配置类记录名
  String __fastcall GetRecordName(){return m_RecordName;} //读取配置类记录名
  void __fastcall AddOptionRecord(TComponent * GUI_Component); //增加一个选项
  void __fastcall GUI2Value();     //从GUI控件读取所有数值
  void __fastcall Value2GUI();     //刷新GUI控件上所有显示的数值
  bool __fastcall Less(const String &OptionName,Variant Value);       //小于比较 <
  bool __fastcall Same(const String &OptionName,Variant Value);       //等于比较 ==
  bool __fastcall Greater(const String &OptionName,Variant Value);    //大于比较 >
  bool __fastcall LessAndSame(const String &OptionName,Variant Value);   //小于等于比较<=
  bool __fastcall GreaterAndSame(const String &OptionName,Variant Value);//大于等于比较>=
  bool __fastcall AsBool(const String &OptionName);
  int  __fastcall AsInt(const String &OptionName);
  String __fastcall AsString(const String &OptionName);
  double __fastcall AsDouble(const String &OptionName);
  DWORD  __fastcall AsDWORD(const String &OptionName);
  virtual bool    LoadFromFile(const String &FileName,const String &SecName);
  virtual void    SaveToFile(const String &FileName);
  virtual bool    LoadFromIni(TMemIniFile * IniFile,const String &SecName);
  virtual void    SaveToIni(TMemIniFile * IniFile);
  void __fastcall SetValue(const String &OptionName,Variant Value);   //设置某项的数值
  Variant __fastcall GetValue(const String &OptionName);              //获取某项的数值
};

#endif
