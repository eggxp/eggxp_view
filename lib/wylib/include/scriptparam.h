//---------------------------------------------------------------------------

#ifndef ScriptParamH
#define ScriptParamH
#include <Classes.hpp>
#include "alist.h"
//脚本的用户扩展函数对象
struct WYParam
{
	Variant  Value;     //参数的值
	String   Name;      //参数名称
	String   Info;	  //参数说明
	int      Type;   //0=数值  1=字符串
};
//参数对象
class WY_Params
{
private:
   AList<WYParam> * m_ParamList; //参数列表
protected:
   int				m_RunTimeCount; //运行期间真实参数个数
public:
   WY_Params();
   ~WY_Params();
   int 		Count(){return m_ParamList->Count();}  //预定义参数个数
   int		RunTimeCount(){return m_RunTimeCount;}   	 //运行期间真实参数个数
   WYParam * Add(const String &ParamName,const String &Info,Variant  Value,int Type);  //新建一个参数
   WYParam * Get(const String &ParamName);      //某参数是否存在
   WYParam * At(int Index){return m_ParamList->At(Index);}
   Variant  ValueByName(const String &ParamName); //根据名字获取此参数的值
   Variant  ValueByIndex(int Index); //根据Index获取此参数的值
   bool ReadFromStrings(TStrings * ParamStr);    //从一个TStrings中读取数值
   void Assign(WY_Params * OtherParams);
   void Clear(){m_ParamList->Clear();}
};


//---------------------------------------------------------------------------
#endif
