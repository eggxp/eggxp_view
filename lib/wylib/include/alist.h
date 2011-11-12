//---------------------------------------------------------------------------
//动态指针数组容器管理类
//特性(设计目标):
//基于vector封装,提供一个类似于VCL的TList的接口
//可以自动释放元素,list保存元素指针以节省内存空间


//构造时间: 2004.08.24
//修改记录: 2004.08.24
//修改记录: 2005.01.19  增加了Sort函数,采用快速排序法
//修改记录: 2005.03.12  修改了Add函数,在数组满的时候,自动扩大数组
//修改记录: 2006.06.06  修正了alist.h模板类delete函数和move函数可能导致内存泄漏的bug(徐星发现的bug)
//作者: Bluely

//---------------------------------------------------------------------------
#ifndef alistH
#define alistH
#include <vector>
using namespace std;
#define  AERR_ARRAY_FULL -1
#define  AERR_NOERR     0
//定义函数类型,用于排序比较
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T> class AList
{
  typedef int (*CListSortCompare)(T * Item1, T * Item2);
  /*用户自定义函数,用于比较两个元素的大小,排序函数必须用到
  //举例: 要按照从小到大排序

  int ComparASC(T *Item1, T *Item2)
  {
    if (Item1  < Item2)
    {
      return 1;
    }
    else if(Item1 == Item2)
    {
      return 0;
    }
    else if(Item1 > Item2)
    {
      return -1;
    }
    else
    {
      return 0;
    }
  }
  //按照从大到小的顺序排序
  int ComparLow(T *Item1, T *Item2)
  {
    if (Item1  > Item2)
    {
      return 1;
    }
    else if(Item1 == Item2)
    {
      return 0;
    }
    else if(Item1 < Item2)
    {
      return -1;
    }
    else
    {
      return 0;
    }
  }*/
  private:
     bool    m_IsAutoFree;
  protected:
     vector<T *>  IndexTable;
     int          m_TrueSize;
     int          m_MaxSize;
     void         QuickSort(int L, int R,CListSortCompare SCompare);
  public:
     AList(bool IsAutoFree = true,int MaxSize = 10);  //参数指明移除元素的时候，是否自动调用delete释放删除元素
     ~AList();
     __inline int    Count(){return m_TrueSize;}      //返回元素的总数
     __inline int    MaxSize(){return m_MaxSize;}     //返回容器总大小
	 bool   Add(T *Data,bool AddToFirst=false);      //添加一个元素,如果存在则覆盖他的值,AddToFirst如果为真,那么将会插入到第一个元素 ,为假则插入到最后一个元素
     T *    At(int Index);     //根据Index获得一个元素
     T *   operator[](int Index){return At(Index);}
     void   Clear();           //清空
     int    IndexOf(T *Data);  //根据T获得元素的Index
     void   Delete(int Index);  //删除一个元素
     T *    First();            //返回第一个元素
     T *    Last();             //返回最后一个元素
     void   Pack();             //整理数组,移除所有为NULL的元素
     int    Remove(T *Data);    //移除某个元素
     void   Exchange(int Index1,int Index2);   //交换两个元素的值
     void   Move(int DesIndex,int SrcIndex);   //将一个元素的值移动到另一个位置
     int    LastError;
     void   SetNULL(int Index);
	 void   Insert(int Index,T *Data);
	 void   Replace(int Index,T*Data); //用一个新元素替换某位置上的旧元素(自动释放旧元素)
     void   Sort(CListSortCompare SortCompareFunc);
     void   ReSize(int NewSize); //重新分配数组总大小,会清空所有的数据

};

//---------------------------------------------------------------------------
template <class T>   AList<T>::AList(bool IsAutoFree,int MaxSize)
{
	   if (MaxSize <=0)
	   	 MaxSize = 1;
     m_IsAutoFree =   IsAutoFree;
     ReSize(MaxSize);
     LastError = AERR_NOERR;
}
//---------------------------------------------------------------------------
template <class T>   AList<T>::~AList()
{
     Clear();
}
//---------------------------------------------------------------------------
template <class T>  void AList<T>::ReSize(int NewSize)
{
     m_TrueSize = 0;
     Clear();
     m_MaxSize =   NewSize;
     IndexTable.reserve(m_MaxSize);
     for (int i=0;i<m_MaxSize;i++)
      IndexTable.push_back(NULL);
}
//---------------------------------------------------------------------------
template<class T>
bool AList<T>::Add(T *Data,bool AddToFirst)
{
    if(m_TrueSize >= m_MaxSize)                     //已经满了
    {
        int OldSize = m_MaxSize;
        m_MaxSize = m_MaxSize * 2;       //扩大新数组为原来的一倍
        for(int i = 0; i < OldSize;i++) //添加新元素
        {
            IndexTable.push_back(NULL);
        }
    }
	if(AddToFirst)
	{
     	Insert(0,Data);
	}
	else
	{
		IndexTable[m_TrueSize] = Data;
		m_TrueSize++;
	}
    return true;
}
//---------------------------------------------------------------------------
template <class T>  void  AList<T>::Insert(int Index,T *Data)
{
    if (m_TrueSize>=m_MaxSize)   //预留空间不足了
    {
        int OldSize = m_MaxSize;
        m_MaxSize = m_MaxSize * 2;
        for(int i = 0; i < OldSize;i++) //添加新元素
        {
			IndexTable.push_back(NULL);
        }
	}
	if (m_TrueSize ==0)      //还没有元素,直接插入
	{
	   IndexTable[m_TrueSize] = Data;
	   m_TrueSize++;
	   return;
	}
	if (Index>=0 && Index<m_TrueSize)
	{
	   //当前index开始的元素指针往后挪动
	   m_TrueSize++; //元素个数加1
	   memmove(&IndexTable[Index+1],&IndexTable[Index],(m_TrueSize-Index-1)*sizeof(T *));
	   IndexTable[Index] = Data;  //放置新元素
	}
}
//---------------------------------------------------------------------------
template <class T>  int  AList<T>::IndexOf(T *Data)
{
    if (Data == NULL)
      return -1;
    for (int i=0;i<m_TrueSize;i++)
    {
       if (IndexTable[i] == Data)
         return i;
    }
    return -1;
}
//----------------------------------------------------------------------------
template <class T>  T *   AList<T>::At(int Index)
{
    if (Index>=0 &&  Index<m_TrueSize)
    {
      return  IndexTable[Index];
    }
    else
     return NULL;
}
//----------------------------------------------------------------------------
template <class T>  void  AList<T>::Clear()
{
   for (int i=0;i<m_TrueSize;i++)
   {
     if (m_IsAutoFree && IndexTable[i] != NULL)
       delete IndexTable[i];
       IndexTable[i] = NULL;
   }
   m_TrueSize = 0;
}
//----------------------------------------------------------------------------
template <class T> void  AList<T>::Delete(int Index)
{
  if (Index>=0 && Index<m_TrueSize)
  {
    if (m_IsAutoFree && IndexTable[Index]!=NULL)
      delete  IndexTable[Index];
    IndexTable[Index] = NULL;
	if (Index < m_TrueSize-1)  //如果不是最后一个元素,搬动
	memcpy(&IndexTable[Index],&IndexTable[Index+1],(m_TrueSize-(Index+1))*sizeof(T *));
    m_TrueSize --;
  }
}
//----------------------------------------------------------------------------
template <class T> void  AList<T>::SetNULL(int Index)
{
  if (Index>=0 && Index<m_TrueSize)
  {
    if (m_IsAutoFree && IndexTable[Index]!=NULL)
      delete  IndexTable[Index];
    IndexTable[Index] = NULL;
  }
}
//----------------------------------------------------------------------------
template <class T> T *  AList<T>::First()
{
   if (m_TrueSize>0)
     return   IndexTable[0];
   else
     return NULL;
}
//----------------------------------------------------------------------------
template <class T> T *  AList<T>::Last()
{
   if (m_TrueSize>0)
     return   IndexTable[m_TrueSize-1];
   else
     return NULL;
}
//----------------------------------------------------------------------------
template <class T> void  AList<T>::Pack()
{
   for (int i=m_TrueSize-1;i>=0;i--)
   {
      if (IndexTable[i] == NULL)
      {
        Delete(i);
      }
   }
}
//----------------------------------------------------------------------------
template <class T> int  AList<T>::Remove(T *Data)
{
   int Index =   IndexOf(Data);
   if (Index>=0)
   {
     Delete(Index);
   }
   return Index;
}
//---------------------------------------------------------------------------
template <class T> void  AList<T>::Exchange(int Index1,int Index2)
{
   T * tempEm;
   if (Index1<0 || Index1>=m_TrueSize || Index2<0 || Index2>=m_TrueSize)
   {
      return;
   }
   tempEm = IndexTable[Index1];
   IndexTable[Index1] =   IndexTable[Index2];
   IndexTable[Index2] =   tempEm;
}
//---------------------------------------------------------------------------
template <class T> void  AList<T>::Move(int DesIndex,int SrcIndex)
{
   if (DesIndex == SrcIndex)
     return;
   if (DesIndex<0 || DesIndex>=m_TrueSize || SrcIndex<0 || SrcIndex>=m_TrueSize)
     return;
   if  (IndexTable[DesIndex]!=NULL && m_IsAutoFree)
   {
      delete  IndexTable[DesIndex];
   }
   IndexTable[DesIndex] = IndexTable[SrcIndex];
   if (SrcIndex < m_TrueSize-1)  //如果不是最后一个元素,搬动
    memcpy(&IndexTable[SrcIndex],&IndexTable[SrcIndex+1],(m_TrueSize-(SrcIndex+1))*sizeof(T *));
   m_TrueSize --;
}
//---------------------------------------------------------------------------
template <class T> void  AList<T>::Replace(int Index,T*Data)
{
   if (Index<0 || Index>=m_TrueSize)
     return;
   if  (IndexTable[Index]!=NULL && m_IsAutoFree)    //自动释放原来的元素
   {
      delete  IndexTable[Index];
   }
   IndexTable[Index] = Data; //将新元素放到原来的位置
}
//---------------------------------------------------------------------------
template <class T> void  AList<T>::Sort(CListSortCompare SortCompareFunc)
{
  if (Count() > 1)
  {
    QuickSort(0,Count() - 1,SortCompareFunc);
  }
}
//---------------------------------------------------------------------------
template <class T> void  AList<T>::QuickSort(int L, int R,CListSortCompare SCompare)
{
  int I=0;
  int J=0;
  int Half;
  T *P=NULL;
  T* t=NULL;
  do
  {
    I = L;
    J = R;
    Half = (L + R) >> 1;
    P = IndexTable[Half];
    do
    {
      while (SCompare(IndexTable[I],P) < 0)
      {
        I++;
      }
      while (SCompare(IndexTable[J],P) > 0)
      {
        J--;
      }
      if (I <= J)
      {
        t = IndexTable[I];
        IndexTable[I] = IndexTable[J];
        IndexTable[J] = t;
        I++;
        J--;
      }
    }
    while (I <= J);
    if (L < J)
    {
      QuickSort(L,J,SCompare);
    }
    L = I;
  }
  while (I < R);
}
//---------------------------------------------------------------------------
#endif
