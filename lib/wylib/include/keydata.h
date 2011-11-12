//---------------------------------------------------------------------------
/*
提供一个数据基类和一个容器管理类
以实现通用的按Key索引和按Name索引容器管理,所有的数据只需要从AKeyData继承下来,重载实现接口虚拟函数,然后将数据加入AIndexManage中,即获得按Key查找,按Name查找，按Index查找之能力
作者: 林弋
最后修改日期: 2004.12.04


*/
#ifndef keydataH
#define keydataH
#include <vcl.h>
#include "alist.h"
#include "amap.h"
//数据接口类
//---------------------------------------------------------------------------
class AKeyData
{
  private:
  protected:
  public:
     __fastcall AKeyData(){;}
     virtual __fastcall ~AKeyData(){return;}
     virtual DWORD   GetKey()=0;
     virtual String  GetName()=0;
     virtual int     ReadData(char *buf)=0;  //从缓冲区读取数据,返回读取数据的值
	 virtual void    Reset()=0;
     virtual void    Assign(AKeyData *SrcData)=0; //从另外一个对象拷贝
};

class AIndexManage
{
private:
   AIndexList<AKeyData> *DataList;
protected:

public:
  __fastcall AIndexManage(int MaxRecord=10000);
  virtual __fastcall ~AIndexManage();
  int      IndexOf(DWORD KeyID);
  int      IndexOfName(String Name);
  __inline int Count(){return DataList->Count();}
  AKeyData * Get(DWORD KeyID);
  AKeyData * GetByName(String Name);
  __inline AKeyData * At(int Index){return DataList->At(Index);}
  bool  Add(AKeyData * KeyData);
  void  Delete(int Index){DataList->Delete(Index);}
  void  DeleteByKey(DWORD Key){DataList->Delete(IndexOf(Key));}
  __inline void  Clear(){DataList->Clear();}
  String   GetName(DWORD ID);


};


#endif
