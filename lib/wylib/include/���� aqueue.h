//---------------------------------------------------------------------------

#ifndef aqueueH
#define aqueueH
#include <queue>
#include "alist.h"

// 队列,优先队列,堆栈容器管理类

//构造时间: 2005.01.19
//作者: Bluely
//基于AList的队列类

//AQueue         队列,先进先出
//APriorityQueue 优先级队列,插入排序,基于快速排序法,目前效率不高,等待用堆排序重新实现
//AStack         堆栈类,先进后出
template <class T> class AQueue
{
  private:
     AList<T> *DataTable; //存放数据的地方
  protected:
  public:
     AQueue(int MaxSize = 1000)
     {
        DataTable = new AList<T>(false,MaxSize);  //参数指明移除元素的时候，是否自动调用delete释放删除元素
     }
     ~AQueue(){delete DataTable;}
     void Push(T *Data){DataTable->Add(Data);}
     T *Pop()
     {
       if (Count()<=0)
       {
          return NULL;
       }
       T * Result = DataTable->At(0);
       DataTable->Delete(0);
       return Result;
     };
     void Clear(){DataTable->Clear();} //清空队列,但不释放队列里面的元素
     void FreeAndClear()
     {
       T *CurData;      //释放队列里面的元素并且清空队列
       while (Count()>0)
       {
          CurData = Pop();
          delete  CurData;
       }
       Clear();
     }
     __inline T *   At(int Index){return DataTable->At(Index);}
     __inline int Count(){return DataTable->Count();}
};

//基于STL   PriorityQueue的优先级队列(堆排序)    ,未完成
/*
template <class T> class APriorityQueue
{
    class CTypePtr   //节点指针类，< 操作符重载以后，用来指定priority_queue的排序结果是从小到大
    {
    public:
        T* ptr;

        CTypePtr(T * node)
        {
                ptr = node;
        }

        operator CTypePtr *() const
        {
                return ptr;
        }

        bool operator < (const CTypePtr& other) const     //重载<比较操作符，用于更改排序操作结果
        {
            return ((*ptr) > (*other));
        }

        bool operator == (const CTypePtr& other) const
        {
           return ( (*ptr) == (*other));
        }
    };
   typedef std:: priority_queue<CTypePtr> NodeQueue;
   private:
     NodeQueue    PQueue;
   protected:
   public:
     void Push(T *Data);
     T *Pop()
     {
       if (Count()<=0)
       {
          return NULL;
       }
       T * Result = DataTable->At(0);
       DataTable->Delete(0);
       return Result;
     };
     void Clear(){DataTable->Clear();} //清空队列,但不释放队列里面的元素
     void FreeAndClear()
     {
       T *CurData;      //释放队列里面的元素并且清空队列
       while (Count()>0)
       {
          CurData = Pop();
          delete  CurData;
       }
       Clear();
     }
     __inline T *   At(int Index){return DataTable->At(Index);}
     __inline int Count(){return PQueue.Count();}
};     */

//基于AList的 优先级队列,性能不佳，等待重新实现
//CListSortCompare例子
/*int ComparDistance(A *Item1, A *Item2)
{
  if (Item1->Dis  < Item2->Dis)
  {
    return 1;
  }
  else if(Item1->Dis == Item2->Dis)
  {
    return 0;
  }
  else if(Item1->Dis > Item2->Dis)
  {
    return -1;
  }
  else
  {
    return 0;
  }
} */
template <class T> class APriorityQueue
{
  typedef int (*CListSortCompare)(T * Item1, T * Item2);
  private:
     AList<T> *DataTable; //存放数据的地方
  protected:
    CListSortCompare _SortCompareFunc;
  public:
     APriorityQueue(CListSortCompare SortCompareFunc,int MaxSize = 1000)
     {
        DataTable = new AList<T>(false,MaxSize);  //参数指明移除元素的时候，是否自动调用delete释放删除元素
        _SortCompareFunc =   SortCompareFunc;
     }
     ~APriorityQueue(){delete DataTable;}
     void Push(T *Data){DataTable->Add(Data);DataTable->Sort(_SortCompareFunc);}
     T *Pop()
     {
       if (Count()<=0)
       {
          return NULL;
       }
       T * Result = DataTable->At(0);
       DataTable->Delete(0);
       return Result;
     };
     void Clear(){DataTable->Clear();} //清空队列,但不释放队列里面的元素
     void FreeAndClear()
     {
       T *CurData;      //释放队列里面的元素并且清空队列
       while (Count()>0)
       {
          CurData = Pop();
          delete  CurData;
       }
       Clear();
     }
     __inline T *   At(int Index){return DataTable->At(Index);}
     __inline int Count(){return DataTable->Count();}

};

//基于AList的堆栈类
template <class T> class AStack
{
  private:
     AList<T> *DataTable; //存放数据的地方
  protected:
  public:
     AStack(int MaxSize = 1000)
     {
        DataTable = new AList<T>(false,MaxSize);  //参数指明移除元素的时候，是否自动调用delete释放删除元素
     }
     ~AStack(){delete DataTable;}
     void Push(T *Data){DataTable->Add(Data);}
     T *Pop()
     {
       if (Count()<=0)
       {
          return NULL;
       }
       T * Result = DataTable->At(Count()-1);
       DataTable->Delete(Count()-1);
       return Result;
     };
     void Clear(){DataTable->Clear();} //清空队列,但不释放队列里面的元素
     void FreeAndClear()
     {
       T *CurData;      //释放队列里面的元素并且清空队列
       while (Count()>0)
       {
          CurData = Pop();
          delete  CurData;
       }
       Clear();
     }
     __inline T *   At(int Index){return DataTable->At(Index);}
     __inline int Count(){return DataTable->Count();}
};
//---------------------------------------------------------------------------
#endif
