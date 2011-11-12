//---------------------------------------------------------------------------


#pragma hdrstop

#include "fsm.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
int  CTransitionEvent::DoBeforeAction()  //状态转换之 "前" 执行事件动作
{
	  if (m_BeforeEventAction!=NULL)
	  {
		 m_BeforeEventAction();
	  }
	  return _DesStauID;
}
//---------------------------------------------------------------------------
void  CTransitionEvent::DoAfterAction()  //状态转换之 "后" 执行事件动作
{
	  if (m_AfterEventAction!=NULL)
	  {
		 m_AfterEventAction();
	  }
}
//---------------------------------------------------------------------------
__fastcall CStat::CStat(int StatID,int StatImageIndex,String StatInfo,String Hint)
{
    _ID         = StatID;
    _ImageIndex = StatImageIndex;
    _Info       = StatInfo;
    _Hint       = Hint;
    TranstionList   = new  AList<CTransitionEvent>(true,100);
}
//---------------------------------------------------------------------------
__fastcall CStat::~CStat()
{
    delete TranstionList;
}
//---------------------------------------------------------------------------
int   CStat::GetTEIndex(int EventID)
{
   CTransitionEvent *TranEvent;
   for (int i=0;i<TranstionList->Count();i++)
   {
      TranEvent = TranstionList->At(i);
      if (TranEvent->GetEventID() == EventID)
      {
         return i;
      }
   }
   return -1;
}
//---------------------------------------------------------------------------
//  //增加一个事件处理对象
bool __fastcall  CStat::AddTransitionEvent(CTransitionEvent *NewTE)
{
    if (NewTE==NULL || GetTEIndex(NewTE->GetEventID())>=0)   //对象无效或对象已经存在
    {
        return false;
	}
    TranstionList->Add(NewTE);
    return true;
}
//---------------------------------------------------------------------------
CTransitionEvent *  __fastcall  CStat::AddTransitionEvent(int EventID,TFUN_EVENT_ACTION BeforeEventAction,TFUN_EVENT_ACTION AfterAction,int DesStauID)
{
	if (GetTEIndex(EventID)>=0)   //对象无效或对象已经存在
	{
		return NULL;
	}
	CTransitionEvent *NewTE = new CTransitionEvent(EventID,BeforeEventAction,AfterAction,DesStauID);
	if (AddTransitionEvent(NewTE))
	{
	   return NewTE;
	}
	else
	{
	   delete  NewTE;
	   return NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall CStat::EventSuccess(int EventID)
{
   int TEIndex = GetTEIndex(EventID);
   if (TEIndex==-1)
   {
	 return;
   }
   CTransitionEvent *TranEvent;
   TranEvent = TranstionList->At(TEIndex);
   if (TranEvent==NULL)
   {
	 return;
   }
   TranEvent->DoAfterAction();
}
//---------------------------------------------------------------------------
int __fastcall CStat::Transition(int EventID)
{
   int TEIndex = GetTEIndex(EventID);
   if (TEIndex==-1)
   {
	 return -1;
   }
   CTransitionEvent *TranEvent;
   TranEvent = TranstionList->At(TEIndex);
   if (TranEvent==NULL)
   {
	 return -1;
   }
   return TranEvent->DoBeforeAction(); //执行事件对应的动作函数,返回下一个状态
}
//状态管理类
//---------------------------------------------------------------------------
__fastcall CFSM_Manage::CFSM_Manage()
{
    StatList = new  AList<CStat>(true,1000);
    OnStausChanage = NULL;
}
//---------------------------------------------------------------------------
__fastcall CFSM_Manage::~CFSM_Manage()
{
    delete  StatList;
}
//----------------------------------------------------------------------------
int   CFSM_Manage::GetStatIndex(int StatID)
{
   CStat *Stat;
   for (int i=0;i<StatList->Count();i++)
   {
      Stat = StatList->At(i);
      if (Stat->GetID() == StatID)
      {
         return i;
      }
   }
   return -1;
}
//----------------------------------------------------------------------------
CStat *    CFSM_Manage::GetStat(int StatID) //根据ID获取状态对象
{
    return StatList->At(GetStatIndex(StatID));
}
//----------------------------------------------------------------------------
bool __fastcall  CFSM_Manage::Add(CStat *NewStat)
{
	if (NewStat==NULL || GetStatIndex(NewStat->GetID())>=0)   //对象无效或对象已经存在
	{
		return false;
    }
	StatList->Add(NewStat);
    return true;
}
//----------------------------------------------------------------------------
CStat * CFSM_Manage::Add(int StatID,int StatImageIndex,String StatInfo,String Hint)
{
	if (GetStatIndex(StatID)>=0)
	{
		return NULL;
	}
	CStat *NewStat  = new CStat(StatID,StatImageIndex,StatInfo,Hint);
	if (Add(NewStat))
	{
	   return  NewStat;
	}
	else
	{
	   delete  NewStat;
	   return NULL;
	}
}
//----------------------------------------------------------------------------
int __fastcall CFSM_Manage::Transition(int EventID)
{
   CStat * OldStat =  GetStat(_CurrentStatID);
   if (OldStat==NULL) //当前处于未定义状态
	return -1;
   int DesStat =  OldStat->Transition(EventID);
   if (DesStat==-1)    //执行转换动作失败(事件类型错误)
   {
	   return -1;
   }
   _CurrentStatID = DesStat;  //成功，将当前状态设置成切换后的状态
   OldStat->EventSuccess(EventID);
   if (OnStausChanage)
   {
	   OnStausChanage(OldStat,GetCurrentStat());
   }
   return 1;
}
//----------------------------------------------------------------------------
void __fastcall CFSM_Manage::SetStat(int NewStatID)
{
    _CurrentStatID=NewStatID;
   if (OnStausChanage)
   {
       OnStausChanage(GetCurrentStat(),GetCurrentStat());
   }

}

//----------------------------------------------------------------------------
void     CFSM_Manage::RefreshGUI()
{
   if (OnStausChanage)
   {
       OnStausChanage(GetCurrentStat(),GetCurrentStat());
   }
}
