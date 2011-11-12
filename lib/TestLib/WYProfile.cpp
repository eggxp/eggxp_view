//---------------------------------------------------------------------------


#pragma hdrstop

#include "WYProfile.h"
#include "counttime.h"
#include "alist.h"

//---------------------------------------------------------------------------
static CProfileManager * ProfileMgr=NULL;
#pragma package(smart_init)


CProfileNode::CProfileNode(String Name)
{
	m_Name = Name;
	m_LastCountValue = 0;
	m_CountTimes = 0;
	m_Parent	= NULL;
	m_TimeCount = new CTimeCount();
	m_ChildList = new  AIndexListPro<String,CProfileNode>(true);
}
//---------------------------------------------------------------------------
CProfileNode::~CProfileNode()
{
   delete m_ChildList;
   delete m_TimeCount;

}
//---------------------------------------------------------------------------
void	CProfileNode::Start()
{
	  m_CountTimes++;
	  m_TimeCount->BeginCount();
}
//---------------------------------------------------------------------------
void	CProfileNode::End()
{
	 m_LastCountValue =  m_TimeCount->EndCount();
}
//---------------------------------------------------------------------------
void    CProfileNode::Clear()
{
	m_LastCountValue = 0;
	m_CountTimes = 0;
	return m_ChildList->Clear();
}

//---------------------------------------------------------------------------
double	CProfileNode::GetPercent()
{
	if (m_Parent && m_Parent->GetCountValue()>0)
	{
		return (m_LastCountValue/m_Parent->GetCountValue())*100;
	}
	return 100;
}
//---------------------------------------------------------------------------
CProfileNode * CProfileNode::GetChild(String Name)
{
	 CProfileNode * p_Child = m_ChildList->Find(Name);
	 if (p_Child==NULL)
	 {
		 p_Child = new  CProfileNode(Name);
		 p_Child->SetParent(this);
		 m_ChildList->AddEx(Name,p_Child);
	 }
	 return  p_Child;
}
//---------------------------------------------------------------------------
CProfileManager * CProfileManager::GetIns()
{
	if (ProfileMgr==NULL)
	{
		ProfileMgr = new  CProfileManager();
	}
	return ProfileMgr;
}
//---------------------------------------------------------------------------
CProfileManager::CProfileManager()
{
    m_RootNode = new CProfileNode("root");
    m_CurrentNode = m_RootNode;
    m_SelecttViewNode = m_RootNode;
}
//---------------------------------------------------------------------------
CProfileManager::~CProfileManager()
{
   Reset();
   delete  m_RootNode;
   m_RootNode = NULL;
}

//---------------------------------------------------------------------------
void     CProfileManager::SetName(String name)
{
    m_Name = name;

    if(name == "")
        m_Name = "ProfileSample";
}

//---------------------------------------------------------------------------
String   CProfileManager::GetName()
{
    if(m_Name == "")
        return  "ProfileSample";
    return  m_Name;
}
//---------------------------------------------------------------------------
void CProfileManager::StartProfile(const char * Name)
{
	String ProfileName =String(Name);
    ProfileName.Unique();
	if (m_CurrentNode->GetName() != ProfileName)
	{
		m_CurrentNode =    m_CurrentNode->GetChild(ProfileName);
		//开始统计
		m_CurrentNode->Start();
	}
}
//---------------------------------------------------------------------------
void CProfileManager::Stopprofile()
{
	m_CurrentNode->End();
	if (m_CurrentNode->GetParent() == m_RootNode)
	{
		//累加根节点统计值
	   m_RootNode->IncCount(m_CurrentNode->GetCountValue());
	}
	m_CurrentNode = m_CurrentNode->GetParent();

}
//---------------------------------------------------------------------------
void CProfileManager::Reset()
{
//	for (int i = 0; i < m_RootNode->ChildCount(); i++)
//	{
//	   m_RootNode->GetChildByIndex(i)->Clear();
//	}
	m_RootNode->Clear();
}

void CProfileManager::SetSelecttViewNode(CProfileNode * Node)
{
	if (Node)
	  m_SelecttViewNode= Node;
}

///////////////////////////////////////////////////////////////////////////

CThreadProfileManager::CThreadProfileManager()
{
    m_bIsNeedWatch = false;
    fpOnWatch = NULL;
}

CThreadProfileManager::~CThreadProfileManager()
{
}

void            CThreadProfileManager::SetNeedWatch(TWatchFunc   watchFunc)
{
    fpOnWatch = watchFunc;
    m_bIsNeedWatch = true;
}

void    __fastcall      CThreadProfileManager::WatchInfo()
{
    if(m_bIsNeedWatch && fpOnWatch)
    {
        fpOnWatch(this);
        m_bIsNeedWatch = false;
    }
}

void            CThreadProfileManager::Reset()
{
    CProfileManager::Reset();
    m_bIsNeedWatch = false;
}
