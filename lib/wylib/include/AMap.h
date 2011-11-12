//容器效率和适用场合
//
//速度说明:
//常数   直接存取   非常快
//线性   循环查找   越往后的元素越慢,元素越多越慢
//对数   log(n)     快,比直接存取慢一点点log(10000) = 4 log(100000)=5  log(1000000)=6,元素数量多一位数,查找时间就比直接存取增加一倍
//
//
//	
//容器名			随机存取速度At(i)		按Key查找速度  		内存结构  		内存消耗		 随机添加和删除速度      推荐适用场合
//AList			  常数(直接存取)  	线性           		 顺序存放  		  小(无额外开销)   快       					元素数量不多,并且不需要根据Key频繁查找的场合
//AIndexMap       线性            	对数           		 Btree     		  中               快    					Key=Value形式组织的数据场合,需要根据Key频繁查找Value的场合,无需根据Index直接存取的场合
//AIndexHashMap   线性                ~=对数(取决于           哈希桶    		较大			   快    					Key=Value形式组织的数据场合,需要根据Key频繁查找Value的场合,无需根据Index直接存取的场合
//                                        Hash函数碰撞率)
//AIndexList      常数(直接存取)      对数                  顺序存放(但排序元素)    中		 快					即需要按Key快速查找,又需要Index直接存取的场合,但是元素自动排序,所以不适用于要求元素保持原始顺序的场合使用
//AIndexListPro   常数(直接存取)      对数                  顺序存放(但排序元素)    中		 线性(越前面越慢)	即需要按Key快速查找,又需要Index直接存取的场合,但是元素自动排序,所以不适用于要求元素保持原始顺序的场合使用

//大部分场合,推荐使用AIndexList
//---------------------------------------------------------------------------
//amap.h
//---------------------------------------------------------------------------
//以下所有容器维护的皆是对象的指针,而不是对象的实体,所以比较适合存放类和结构,不适合存放原始数据类型比如int,DWORD
//

//////////////////////////////////////////////////////////////////////////////////
//名称:    AIndexMap                                                            //
//////////////////////////////////////////////////////////////////////////////////
//介绍:   基于STL Map封装的Map类(平衡二叉树)
//特性:   提供对数时间的快速查找功能, 所有添加进入的元素均有Key关键字用于索引查找,
//        元素存放组织为Btree,快速插入删除,快速查找
//        Key关键字保持唯一
//        保持和AList一样的简易使用接口
//缺点:
//因为Map是关联式容器,元素在内存的实际位置不连续,不支持随机存取,所以At(i)操作函数使用遍历,时间消耗为线性
//BTree相对于vector有额外的内存消耗(存放节点指针)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////
//名称:    AIndexHashMap                                                        //
//////////////////////////////////////////////////////////////////////////////////
//介绍:    基于STL Hash_Map封装的哈西表类,
//特性:    提供接近常数时间的快速查找功能,效率取决于Hash函数,所有添加进入的元素均有
//         Key关键字用于索引查找,元素存放组织形式为Hash散列
//缺点:
//因为Hash_Map是关联式容器,,元素在内存的实际位置不连续,不支持随机存取,所以At(i)操作函数使用遍历,时间消耗为线性
//Hash_Map相对于vector有额外的内存消耗(桶数组,N个链表存放节点指针)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////
//名称:    AIndexList                                                           //
//////////////////////////////////////////////////////////////////////////////////
//介绍:    基于STL vector的索引容器
//特性:    通过内部机制使vector保持排序状态,find函数使用二分查找算法，可以获得log(n)级的搜索速度,
//         同时提供随机存储能力,支持快速At(index)操作,Find搜索之前,会根据排序状态决定是否需要重新排序
//缺点:    初次添加元素后,必须排序. 不适合用在要求元素保持原始顺序的场合

//---------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
//名称: IndexListPro
//介绍 : AIndexList的加强版，支持自定义的KeyType,索引值类型自定义
//自定义的KeyType类型必须支持 == , > ,<比较操作符



//2005.04.04 林弋
#ifndef amapH
#define amapH

#if __BORLANDC__ < 0x0580
#include <hash_map>
#endif
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <vcl.h>



using namespace std;
//------------------------------------------------------------------------------
//map指针容器      AIndexMap
//------------------------------------------------------------------------------
template <class T>  class AIndexMap
{
  typedef map<string,T *,less<string> >::iterator IT_POS;
private:
   map<string,T *,less<string> >  m_DataMap;
   bool    m_IsAutoFree;
protected:

public:
  __fastcall AIndexMap(bool IsAutoFree = TRUE){m_IsAutoFree = IsAutoFree;}
  __fastcall ~AIndexMap(){Clear();}
  void  Clear();
  void  Add(const char * Key,T * lpData);
  T *   Find(const char * Key);
  T *   At(int Index);
  void  Delete(const char * Key);
  __inline int    Count(){return m_DataMap.size();}

};
//----------------------------------------------------------------------------
template <class T>  void  AIndexMap<T>::Clear()
{
   IT_POS Pos;
   for (Pos = m_DataMap.begin();Pos!= m_DataMap.end();++Pos)
   {
     if (m_IsAutoFree && Pos->second != NULL)
     {
       delete  Pos->second;
     }
   }
    m_DataMap.clear();
}
//----------------------------------------------------------------------------
template <class T>  void  AIndexMap<T>::Add(const char * Key,T * lpData)
{
     if (m_IsAutoFree && m_DataMap[Key] != NULL)
     {
       delete  m_DataMap[Key];
     }
    m_DataMap[Key] = lpData; //置放新元素
}
//----------------------------------------------------------------------------
template <class T>  T *  AIndexMap<T>::Find(const char * Key)
{
   IT_POS Pos = m_DataMap.find(Key);
   if (Pos!= m_DataMap.end()) //已经有这个Key值的元素了
   {
      return  Pos->second;    //释放旧元素
   }
   return NULL;
}
//----------------------------------------------------------------------------
template <class T>  T *  AIndexMap<T>::At(int Index)
{
   if (Index>=Count() || Index<0)   //无效索引
    return NULL;
   IT_POS Pos = m_DataMap.begin();
   if (Index==0)
   {
     return  Pos->second;
   }
   advance(Pos,Index);      //遍历
   return  Pos->second;
}

//----------------------------------------------------------------------------
template <class T>  void  AIndexMap<T>::Delete(const char * Key)
{
   IT_POS Pos = m_DataMap.find(Key);
   if (Pos!= m_DataMap.end()) //已经有这个Key值的元素了
   {
       if (m_IsAutoFree && Pos->second != NULL)
       {
          delete  Pos->second;    //释放旧元素
       }
       m_DataMap.erase(Pos);  //移除旧元素
   }
}

#if __BORLANDC__ < 0x0580
//----------------------------------------------------------------------------
//AIndexHashMap   哈西表指针容器
//------------------------------------------------------------------------------
template <class T>  class AIndexHashMap
{
  typedef hash_map<string,T *,hash<string> >::iterator IT_POS;
private:
   hash_map<string,T *,hash<string> >  m_DataMap;
   bool    m_IsAutoFree;
protected:

public:
  __fastcall AIndexHashMap(bool IsAutoFree = TRUE){m_IsAutoFree = IsAutoFree;}
  __fastcall ~AIndexHashMap(){Clear();}
  void  Clear();
  void  Add(const char * Key,T * lpData);
  T *   Find(const char * Key);
  T *   At(int Index);
  void  Delete(const char * Key);
  __inline int    Count(){return m_DataMap.size();}
  __inline int    BucketCount(){return m_DataMap.bucket_count();}
  __inline void   SetBucketCount(int Count){m_DataMap.resize(Count);}

};
//----------------------------------------------------------------------------
template <class T>  void  AIndexHashMap<T>::Clear()
{
   IT_POS Pos;
   for (Pos = m_DataMap.begin();Pos!= m_DataMap.end();++Pos)
   {
     if (m_IsAutoFree && Pos->second != NULL)
     {
       delete  Pos->second;
     }
   }
    m_DataMap.clear();
}
//----------------------------------------------------------------------------
template <class T>  void  AIndexHashMap<T>::Add(const char * Key,T * lpData)
{
     if (m_IsAutoFree && m_DataMap[Key] != NULL)
     {
       delete  m_DataMap[Key];
     }
    m_DataMap[Key] = lpData; //置放新元素
}
//----------------------------------------------------------------------------
template <class T>  T *  AIndexHashMap<T>::Find(const char * Key)
{
   IT_POS Pos = m_DataMap.find(Key);
   if (Pos!= m_DataMap.end()) //已经有这个Key值的元素了
   {
      return  Pos->second;    //释放旧元素
   }
   return NULL;
}
//----------------------------------------------------------------------------
template <class T>  T *  AIndexHashMap<T>::At(int Index)
{
   if (Index>=Count() || Index<0)   //无效索引
    return NULL;
   IT_POS Pos = m_DataMap.begin();
   if (Index==0)
   {
     return  Pos->second;
   }
   advance(Pos,Index);      //遍历
   return  Pos->second;
}

//----------------------------------------------------------------------------
template <class T>  void  AIndexHashMap<T>::Delete(const char * Key)
{
   IT_POS Pos = m_DataMap.find(Key);
   if (Pos!= m_DataMap.end()) //已经有这个Key值的元素了
   {
       if (m_IsAutoFree && Pos->second != NULL)
       {
          delete  Pos->second;    //释放旧元素
       }
       m_DataMap.erase(Pos);  //移除旧元素
   }
}

#endif

//----------------------------------------------------------------------------
//AIndexList   排序的vector模范map set的行为,提供随机存储和log(n)的快速查找能力
//------------------------------------------------------------------------------
typedef size_t (*CSTR_TO_SIZE_T)(const char * StrKey); //自定义Key转换函数
template <class T>  class AIndexList
{
  typedef pair<size_t,T *> T_DATA_TYPE;
  typedef vector<T_DATA_TYPE>::iterator IT_POS;
  class DataCompare    //function obj
  {      // 用于比较的类
  public:
   bool operator()(const T_DATA_TYPE& lhs,   // 用于排序的比较函数
	 const T_DATA_TYPE& rhs) const
   {
		return keyLess(lhs.first, rhs.first); // keyLess在下面
   }
  bool operator()(const T_DATA_TYPE& Ihs,   // 用于查找的比较函数
     const T_DATA_TYPE::first_type& k) const // （形式1,用于lower_bound）
   {
        return keyLess(Ihs.first,k);
   }
   bool operator()(const T_DATA_TYPE::first_type& k,  // 用于查找的比较函数
     const T_DATA_TYPE& rhs) const  // （形式2,用于equal_range）
   {
    return keyLess(k, rhs.first);
   } 

  private:
   bool keyLess(const T_DATA_TYPE::first_type& k1,  // “真的”
     const T_DATA_TYPE::first_type& k2) const // 比较函数
   {
		return (k1 < k2);
   }
  };
private:
   vector<T_DATA_TYPE> m_IndexTable;
   bool    m_IsAutoFree;
   T_DATA_TYPE   KeyValue;
   
protected:
   bool    m_NeedSort; //是否需要先排序才可以查找
   size_t  KeyConv(const char * StrKey)
   {
       if (pfStrToSize_T)
       {
         return pfStrToSize_T(StrKey);
       }
       return atoi(StrKey);
   }
public:
  __fastcall AIndexList(bool IsAutoFree = TRUE){m_IsAutoFree = IsAutoFree;m_NeedSort=false;pfStrToSize_T=NULL;}
  __fastcall ~AIndexList(){Clear();}
  void  Clear();
  //Add函数说明
  //Add函数直接添加元素到最后一个位置,不检查Key重复,添加后的第一次搜索需要重新排序
  //Add函数适合初始化的时候使用
  void  Add(size_t Key,T * lpData);
  //AddEx函数先查找Key值对应的元素是否存在,若存在则替换,保障Key惟一性
  //若不存在,则添加元素到离此Key最近的地方,省去一次排序开销
  //AddEx::函数时候初始化完后动态添加数据时使用
  bool  AddEx(size_t Key,T * lpData);
  T *   Find(size_t Key);
  int   IndexOf(size_t Key);
  T *   At(int Index);
  bool  Delete(size_t Key);
  bool  DeleteByIndex(int index);
  __inline int    Count(){return m_IndexTable.size();}
  void  Sort(){sort(m_IndexTable.begin(), m_IndexTable.end(), DataCompare());m_NeedSort=false;}
  CSTR_TO_SIZE_T  pfStrToSize_T;
};
//------------------------------------------------------------------------------
template <class T> T *   AIndexList<T>::At(int Index)
{
	if (Index>=0 && Index < Count())
	{
	   return  m_IndexTable[Index].second;
	}
	return NULL;
}
//----------------------------------------------------------------------------
template <class T>  void  AIndexList<T>::Clear()
{
   for(int i=0;i<Count() ;i++)
   {
        if (m_IsAutoFree && m_IndexTable[i].second != NULL)
        {
               delete m_IndexTable[i].second;
        }
   }
   m_IndexTable.clear();
}

//----------------------------------------------------------------------------
template <class T>  void  AIndexList<T>::Add(size_t Key,T * lpData)
{
   m_IndexTable.push_back(make_pair(Key,lpData));
   m_NeedSort = true;
}

//----------------------------------------------------------------------------
template <class T>  bool  AIndexList<T>::AddEx(size_t Key,T * lpData)
{
    if (m_NeedSort) //需要排序
    {
       Sort();
    }
    if (Count()==0)
    {
        m_IndexTable.push_back(make_pair(Key,lpData));
        return true;
    }
    IT_POS Pos =  lower_bound(m_IndexTable.begin(),m_IndexTable.end(),Key,DataCompare());   // 在次通过lower_bound查找，
    if (Pos != m_IndexTable.end() && (Pos->first == Key)/*lower_bound函数即使值不存在也会返回某个数据指针,指向最接近的位置*/)
    {
        //已经有这个元素了
        return false;
    }
    //m_IndexTable.insert(Pos,make_pair(Key,lpData));
    if (Pos ==NULL)
    {
        m_IndexTable.push_back(make_pair(Key,lpData));
        return true;
    }
    int Index = Pos - m_IndexTable.begin();
    if (Index<0)
    {
      return false;
    }
    m_IndexTable.push_back(make_pair(Key,lpData));
    memmove(&m_IndexTable[Index+1],&m_IndexTable[Index],(Count()-Index-1)*sizeof(T_DATA_TYPE));
    m_IndexTable[Index].first  = Key;
    m_IndexTable[Index].second = lpData;
    return true;
}

//------------------------------------------------------------------------------
template <class T>   T *   AIndexList<T>::Find(size_t Key)
{
	if (m_NeedSort) //需要排序
	{
	   Sort();
	}
	IT_POS Pos =  lower_bound(m_IndexTable.begin(),m_IndexTable.end(),Key,DataCompare());   // 在次通过lower_bound查找，
	if (Pos != m_IndexTable.end() && (Pos->first == Key)/*lower_bound函数即使值不存在也会返回某个数据指针,指向最接近的位置*/)
	{
		return Pos->second;
	}
	return NULL;
}

//------------------------------------------------------------------------------
template <class T>   int  AIndexList<T>::IndexOf(size_t Key)
{
    if (m_NeedSort) //需要排序
    {
       Sort();
    }
    IT_POS Pos =  lower_bound(m_IndexTable.begin(),m_IndexTable.end(),Key,DataCompare());   // 在次通过lower_bound查找，
    if (Pos != m_IndexTable.end() && (Pos->first == Key)/*lower_bound函数即使值不存在也会返回某个数据指针,指向最接近的位置*/)
    {
        return Pos - m_IndexTable.begin();
    }
    return -1;
}
//---------------------------------------------------------------------------
template <class T> bool  AIndexList<T>::Delete(size_t Key)
{
    int Index = IndexOf(Key);
    return DeleteByIndex(Index);
}
template <class T> bool  AIndexList<T>::DeleteByIndex(int Index)
{
	if (Index >=0 && Index < Count())
	{
		IT_POS Pos = m_IndexTable.begin() + Index;
		if (m_IsAutoFree && Pos->second != NULL)
		{
			delete Pos->second;
		}
		m_IndexTable.erase(Pos);
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------
//AIndexListPro   AIndexList的通用化版, 排序的vector模范map set的行为,提供随机存储和log(n)的快速查找能力
//------------------------------------------------------------------------------
template <class KEYTYPE,class T>  class AIndexListPro
{
  typedef pair<KEYTYPE,T *> T_DATA_TYPE;
  typedef vector<T_DATA_TYPE>::iterator IT_POS;
  class DataCompare    //function obj
  {      // 用于比较的类
  public:
   bool operator()(const T_DATA_TYPE& lhs,   // 用于排序的比较函数
	 const T_DATA_TYPE& rhs) const
   {
		return keyLess(lhs.first, rhs.first); // keyLess在下面
   }
  bool operator()(const T_DATA_TYPE& Ihs,   // 用于查找的比较函数
	 const T_DATA_TYPE::first_type& k) const // （形式1,用于lower_bound）
   {
		return keyLess(Ihs.first,k);
   }
   bool operator()(const T_DATA_TYPE::first_type& k,  // 用于查找的比较函数
	 const T_DATA_TYPE& rhs) const  // （形式2,用于equal_range）
   {
	return keyLess(k, rhs.first);
   } 

  private:
   bool keyLess(const T_DATA_TYPE::first_type& k1,  // “真的”
	 const T_DATA_TYPE::first_type& k2) const // 比较函数
   {
		return (k1 < k2);
   }
  };
private:
   vector<T_DATA_TYPE> m_IndexTable;
   bool    m_IsAutoFree;
   T_DATA_TYPE   KeyValue;

protected:
   bool    m_NeedSort; //是否需要先排序才可以查找
public:
  __fastcall AIndexListPro(bool IsAutoFree = TRUE){m_IsAutoFree = IsAutoFree;m_NeedSort=false;}
  __fastcall ~AIndexListPro(){Clear();}
  void  Clear();
  //Add函数说明
  //Add函数直接添加元素到最后一个位置,不检查Key重复,添加后的第一次搜索需要重新排序
  //Add函数适合初始化的时候使用
  void  Add(KEYTYPE Key,T * lpData);
  //AddEx函数先查找Key值对应的元素是否存在,若存在则替换,保障Key惟一性
  //若不存在,则添加元素到离此Key最近的地方,省去一次排序开销
  //AddEx::函数时候初始化完后动态添加数据时使用
  bool  AddEx(KEYTYPE Key,T * lpData);
  T *   Find(KEYTYPE Key);
  int   IndexOf(KEYTYPE Key);
  T *   At(int Index);
  void  Delete(KEYTYPE Key);
  void	Delete(int Index);
  __inline int    Count(){return m_IndexTable.size();}
  void  Sort(){sort(m_IndexTable.begin(), m_IndexTable.end(), DataCompare());m_NeedSort=false;}
};

//----------------------------------------------------------------------------
template <class KEYTYPE,class T>  void  AIndexListPro<KEYTYPE,T>::Clear()
{
   for(int i=0;i<Count() ;i++)
   {
		if (m_IsAutoFree && m_IndexTable[i].second != NULL)
		{
			   delete m_IndexTable[i].second;
		}
   }
   m_IndexTable.clear();
}

//----------------------------------------------------------------------------
template <class KEYTYPE,class T>  void  AIndexListPro<KEYTYPE,T>::Add(KEYTYPE Key,T * lpData)
{
   m_IndexTable.push_back(make_pair(Key,lpData));
   m_NeedSort = true;
}
//----------------------------------------------------------------------------
template <class KEYTYPE,class T>  bool  AIndexListPro<KEYTYPE,T>::AddEx(KEYTYPE Key,T * lpData)
{
    if (m_NeedSort) //需要排序
    {
       Sort();
    }
    if (Count()==0)
    {
        m_IndexTable.push_back(make_pair(Key,lpData));
        return true;
    }
    IT_POS Pos =  lower_bound(m_IndexTable.begin(),m_IndexTable.end(),Key,DataCompare());   // 在次通过lower_bound查找，
    if (Pos != m_IndexTable.end() && (Pos->first == Key)/*lower_bound函数即使值不存在也会返回某个数据指针,指向最接近的位置*/)
    {
		//已经有这个元素了
		if(m_IsAutoFree)
		{
			//自动释放直接删除
			delete lpData;
        }
        return false;
    }

	if (Pos ==NULL)
	{
		m_IndexTable.push_back(make_pair(Key,lpData));
		return true;
	}
	m_IndexTable.insert(Pos,make_pair(Key,lpData));
	return true;
//	int Index = Pos - m_IndexTable.begin();
//	if (Index<0)
//	{
//	  return false;
//	}
//	m_IndexTable.push_back(make_pair(Key,lpData));
//	memmove(&m_IndexTable[Index+1],&m_IndexTable[Index],(Count()-Index-1)*sizeof(T_DATA_TYPE));
//	m_IndexTable[Index].first  = Key;
//	m_IndexTable[Index].second = lpData;
//	return true;
}
//------------------------------------------------------------------------------
template <class KEYTYPE,class T> T *   AIndexListPro<KEYTYPE,T>::At(int Index)
{
	if (Index>=0 && Index < Count())
	{
	   return  m_IndexTable[Index].second;
	}
	return NULL;
}
//------------------------------------------------------------------------------
template <class KEYTYPE,class T>  T *   AIndexListPro<KEYTYPE,T>::Find(KEYTYPE Key)
{
	if (m_NeedSort) //需要排序
	{
	   Sort();
	}
	IT_POS Pos =  lower_bound(m_IndexTable.begin(),m_IndexTable.end(),Key,DataCompare());   // 在次通过lower_bound查找，
	if (Pos != m_IndexTable.end() && (Pos->first == Key)/*lower_bound函数即使值不存在也会返回某个数据指针,指向最接近的位置*/)
	{
		return Pos->second;
	}
	return NULL;
}
//------------------------------------------------------------------------------
template <class KEYTYPE,class T>  int  AIndexListPro<KEYTYPE,T>::IndexOf(KEYTYPE Key)
{
    if (m_NeedSort) //需要排序
	{
       Sort();
    }
    IT_POS Pos =  lower_bound(m_IndexTable.begin(),m_IndexTable.end(),Key,DataCompare());   // 在次通过lower_bound查找，
    if (Pos != m_IndexTable.end() && (Pos->first == Key)/*lower_bound函数即使值不存在也会返回某个数据指针,指向最接近的位置*/)
    {
        return Pos - m_IndexTable.begin();
    }
    return -1;
}
//---------------------------------------------------------------------------
template <class KEYTYPE,class T> void  AIndexListPro<KEYTYPE,T>::Delete(KEYTYPE Key)
{
    int Index = IndexOf(Key);
    Delete(Index);
}
//----------------------------------------------------------------------------
template <class KEYTYPE,class T>  void  AIndexListPro<KEYTYPE,T>::Delete(int Index)
{
    if (Index >=0 && Index < Count())
    {
		if (m_IndexTable[Index].second && m_IsAutoFree)
		{
		  delete m_IndexTable[Index].second;
		  m_IndexTable[Index].second = NULL;
        }
//		if (Index<Count()-1)
//		{
//		  memcpy(&m_IndexTable[Index],&m_IndexTable[Index+1],(Count()-(Index+1))*sizeof(T_DATA_TYPE));
//		}
//		m_IndexTable.erase(m_IndexTable.end()-1);
		m_IndexTable.erase(m_IndexTable.begin()+Index);
	}
}
//---------------------------------------------------------------------------

#endif
