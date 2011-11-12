//---------------------------------------------------------------------------

#ifndef WYProfileH
#define WYProfileH
//---------------------------------------------------------------------------
#include <vcl.h>
#include "amap.h"
//综合性能评测树
//使用注意
//PROFILE 不是线程安全,
// 如果要在多线程下使用，必须针对这个线程new 一个CProfileManager供这个线程专用
//然后调用THREAD_PROFILE 这个宏
class CTimeCount;
//性能评测节点类

class CProfileNode
{
private:
	AIndexListPro<String,CProfileNode> * m_ChildList;	//属于他的子节点
	CTimeCount  * m_TimeCount;
	double		  m_LastCountValue;
	DWORD		  m_CountTimes;
	CProfileNode  * m_Parent;    //父节点
protected:
	String m_Name;
public:
	CProfileNode(String Name);
	~CProfileNode();
	String  GetName(){return  m_Name;}
	void	SetParent(CProfileNode  * Node){m_Parent=Node;}
	CProfileNode * GetParent(){return  m_Parent;}  //获取父节点
	CProfileNode * GetChild(String Name);	//获取子节点 ,若不存在会创建一个
	int			   ChildCount(){return m_ChildList->Count();}
	CProfileNode * GetChildByIndex(int Index){return m_ChildList->At(Index);}
	void    Clear();		//清除
	void	Start();		//开始本轮评测
	void	End();          //结束本轮评测
	double  GetCountValue(){return m_LastCountValue;}  //获取最后一次统计耗时
	DWORD	GetCountTimes(){return m_CountTimes;}		//获取统计次数
	double	GetPercent();	//获取本统计节点占用父统计节点的百分比
	void	IncCount(double AddCount){m_LastCountValue+=AddCount;} //累加统计时间值
};

//评测数据管理器类
class CProfileManager
{
private:
protected:
	CProfileNode * m_RootNode;  //所有评测点的根节点
	CProfileNode * m_CurrentNode;	//当前节点
	CProfileNode * m_SelecttViewNode; //当选择的观察节点
    String         m_Name;
public:
   CProfileManager();
   virtual  ~CProfileManager();
   static CProfileManager * GetIns();		//
   virtual  void StartProfile(const char * Name);
   virtual  void Stopprofile();
   virtual  void Reset();		//统计复位
   virtual  void SetSelecttViewNode(CProfileNode * Node);
   virtual  void     SetName(String name);
   
   CProfileNode * GetSelecttViewNode(){return m_SelecttViewNode;}

   String   GetName();

   String   Clear();
};

class       CThreadProfileManager;
typedef         void        (__closure  *   TWatchFunc)(CThreadProfileManager   *   profile);
class   CThreadProfileManager : public CProfileManager
{
private:
    bool            m_bIsNeedWatch;
    TWatchFunc      fpOnWatch;
public:
    CThreadProfileManager();
    virtual  ~CThreadProfileManager();

    virtual  void Reset();		//统计复位
    virtual  void SetNeedWatch(TWatchFunc   watchFunc);

    void    __fastcall      WatchInfo();
};


//评测接口类
class CProfileSample
{
private:
	CProfileManager * m_ProfileMgr;
protected:

public:
   CProfileSample(CProfileManager * ProfileMgr,char * Name)
   {
	  m_ProfileMgr = ProfileMgr;
	  ProfileMgr->StartProfile(Name);
   }
   ~CProfileSample()
   {
	  m_ProfileMgr->Stopprofile();
   }
};

//用于单线程
#ifdef ENABLE_PROFILE
#define PROFILE(name) CProfileSample	__profile(CProfileManager::GetIns(),name)
//用于多线程环境
#define THREAD_PROFILE(Ptr_ProfileManager,name) CProfileSample	__profile(Ptr_ProfileManager,name)
#else
#define PROFILE(name) ;
#define THREAD_PROFILE(Ptr_ProfileManager,name) ;
#endif
#endif
