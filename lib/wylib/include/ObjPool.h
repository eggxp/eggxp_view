//---------------------------------------------------------------------------

#ifndef ObjPoolH
#define ObjPoolH
#include "alist.h"
#include <deque>
//---------------------------------------------------------------------------
//指针对象 管理池, 支持随机快速存取,支持快速查找空闲对象和释放空闲对象

//特性(设计目标):
//基于AList实现指针对象管理,并且使用一个deque来管理已分配和未分配对象
//可以自动释放元素,list保存元素指针以节省内存空间

//	内存分配队列算法
//	                          ---------
//      Free(T *)             | FREE   |	<----Get()
//          |                 |--------           |
//          |                 | FREE   |          |
//          |                 |--------           |
//          |                 | FREE   |          |
//          |                 |--------           |
//          |                 | FREE   |          |
//      SetUsed(T *,false)	  |--------           | T * Data = At(0);	//从第一个元素取出
//          |push_back()      | FREE   |          | pop_front();        //移除
//          |                 |--------           | SetUsed(T *,true)   //置为已经使用
//      	|      			  | FREE   |
//          |--------------->  --------
//

//构造时间: 2007.09.21
//作者: Bluely



template <class T> class AObjPool
{
typedef bool (*TCLASS_OPFUNC_IS_USED)(T * Item1);
typedef void (*TCLASS_OPFUNC_SET_USED)(T * Item1,bool Used);
  private:
  protected:
	 AList<T> 	  * TTable;  //元素容器
	 deque<T *>  	IndexTable; //元素索引表 ,
	 int			m_PoolSize;   //池最大大小
  public:
	 int    LastError;
  public:
	 AObjPool(int PoolSize);  //参数指明移除元素的时候，是否自动调用delete释放删除元素
	 ~AObjPool();
	 __inline int    Count(){return TTable->Count();}      //返回元素的总数
	 __inline int    FreeCount(){return IndexTable.size();}   //返回未使用元素的总数
	 bool   Add(T *Data);     //添加一个元素,如果存在则覆盖他的值,AddToFirst如果为真,那么将会插入到第一个元素 ,为假则插入到最后一个元素
	 T *    At(int Index){return TTable->At(Index);}     //根据Index获得一个元素
	 T *    AtFreeQueue(int Index){return IndexTable.at(Index);}  //根据索引从空闲队列获得一个元素
	 T *   operator[](int Index){return At(Index);}
	 int    IndexOf(T *Data){return TTable->IndexOf(Data);}  //根据T获得元素的Index
	 void   Clear();           //清空
	 T	*	Get();			  //从缓冲区里面获取一个空闲的对象
	 void   Free(T * Data);  //删除一个元素
	 bool	IsUsed(T * Data)
	 {
		 if (CB_IsUsedFunc)
		 {
			 return CB_IsUsedFunc(Data);
		 }
		 return false;
	 }
	 void   SetUsed(T * Data, bool Used)
	 {
		if(CB_SetUsedFunc)
		{
		   CB_SetUsedFunc(Data,Used);
		}
	 }
	 TCLASS_OPFUNC_IS_USED	 		 CB_IsUsedFunc;		//测试一个元素是否被使用了,需要使用者根据实际情况指定
	 TCLASS_OPFUNC_SET_USED	 		 CB_SetUsedFunc;       //设置一个元素的使用标志 ,需要使用者根据实际情况实现

};


//---------------------------------------------------------------------------
template <class T>   AObjPool<T>::AObjPool(int PoolSize)
{
	  m_PoolSize  = PoolSize;
	   if (m_PoolSize <=0)
		 m_PoolSize = 1;
	 TTable = new AList<T>(true,m_PoolSize);
	 LastError = AERR_NOERR;
	 CB_IsUsedFunc=NULL;
	 CB_SetUsedFunc=NULL;
}
//---------------------------------------------------------------------------
template <class T>   AObjPool<T>::~AObjPool()
{
	 delete TTable;
}
//---------------------------------------------------------------------------
template <class T>  bool AObjPool<T>::Add(T *Data)
{
	 TTable->Add(Data);
	 IndexTable.push_back(Data);   //第一次加入的元素默认为空闲内存,
	 SetUsed(Data,false); //设置为空闲未使用
	 return true;
}
//---------------------------------------------------------------------------
template <class T>  void AObjPool<T>::Clear()
{
	 IndexTable.clear();
	 TTable->Clear();
}
//---------------------------------------------------------------------------
template <class T>    T	*	AObjPool<T>::Get()
{
		if (FreeCount()<=0)
		{
			return NULL; 		//没有空闲缓冲区了
		}
		T * Data = IndexTable.at(0);   //取出第一个元素
		while(IsUsed(Data))
		{
			//此元素已经被用过,按照正常情况不可能放在空闲队列里面,用户有重复Free错误操作导致
			IndexTable.pop_front();        //删除第一个元素
			Data = IndexTable.at(0); 	   //再次取一个元素
		}
		IndexTable.pop_front();
		SetUsed(Data,true);   //设置为已经使用
		return Data;
}
//---------------------------------------------------------------------------
template <class T> void   AObjPool<T>::Free(T * Data)
{
	   if(!IsUsed(Data))
	   {
		  //标志已经被设置成空闲的,为了防止重复放置,不放到空闲队列
		  return;
       }	
	   SetUsed(Data,false);
	   IndexTable.push_back(Data);  //添加到空闲队列
}
#endif
