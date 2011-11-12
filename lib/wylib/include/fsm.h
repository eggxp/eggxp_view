/** @defgroup FSM 有限状态机实现(fsm.h)
 *  @author  林弋
 *  @version 1.0
 *  @date    2004.11.16
 *  @{
 */
 //sdfasdfa
 //sadfsdafdsf

#ifndef fsmH
#define fsmH
#include <vcl.h>
#include "alist.h"
/**  定义事件发生时候执行的回调函数*/
typedef void  __fastcall (__closure *TFUN_EVENT_ACTION)();

/*! \class CTransitionEvent
    \brief 转换事件管理类,事件转换管理，用于定义状态机转换事件

    此类为CStat类所用
*/
class CTransitionEvent  
{
  private:
   int _EventID;             /**< 事件ID,不能重复 */
	 TFUN_EVENT_ACTION m_BeforeEventAction;    /**< 收到事件状态转变之 ”前“ 执行自定义函数 */
	 TFUN_EVENT_ACTION m_AfterEventAction;     /**< 收到事件状态转变之 “后” 执行自定义函数 */

   int _DesStauID;   /**< 事件触发后的目标状态 */
  public:
       /**
       * 构造函数
       * @param EventID       事件ID,不能重复
       * @param BeforeAction  收到事件状态转变之 ”前“ 执行自定义函数指针
       * @param AfterAction   收到事件状态转变之 “后” 执行自定义函数指针
       * @param DesStauID     目标状态ID,此事件发生后导致转换到目标状态
       * @see ~CTransitionEvent()
       * @return 无
       */
   __fastcall CTransitionEvent(int EventID,TFUN_EVENT_ACTION BeforeAction,TFUN_EVENT_ACTION AfterAction,int DesStauID){_EventID= EventID;m_BeforeEventAction=BeforeAction;m_AfterEventAction = AfterAction; _DesStauID = DesStauID;}
   /** 析构函数
   * 无参数返回值
   */
   __fastcall ~CTransitionEvent(){;}
       /**
       * 获取事件对象的ID
       * @see CTransitionEvent()
       * @return 事件对象的ID(int)
       */
   __inline   int GetEventID(){return _EventID;}
       /**
       * 执行状态转换之 "前" 执行事件动作
	   * @see DoAfterAction()
       * @return 转化后事件对象的ID(int)
	   */
   void  	  DoAfterAction();

	   /**
       * 执行状态转换之 "后" 执行事件动作
       * @see DoBeforeAction()
       * @return 无
	   */
   int        DoBeforeAction();
};
//

/*! \class CStat
    \brief 状态表示类,用于定义状态机的状态,和触发状态切换的事件

    此类为CFSM_Manage类所用
*/
class CStat       
{
private:
  AList<CTransitionEvent> * TranstionList;  /**< 此状态的转换事件列表 */
  int        _ID;                          /**< 此状态的ID */
  int        _ImageIndex;                  /**< 此状态的图形标志索引 */
  String     _Info;                       /**< 此状态的说明 */
  String     _Hint;                      /**< 此状态的详细说明信息 */
protected:
	       /**
       * 获取某事件处理对象的Index
       * @param EventID       事件ID
       * @see AddTransitionEvent()
       * @return 对应事件id的索引
       */
  int        GetTEIndex(int EventID); 
public:
       /**
       * 构造函数
       * @param StatID          状态ID,不能重复
       * @param StatImageIndex  此状态的图形索引ID,用于图形化表示状态
       * @param StatInfo        此状态的文字描述
       * @param Hint            此状态的详细说明
       * @see ~CStat()
       * @return 构造函数默认值
       */
  __fastcall CStat(int StatID,int StatImageIndex,String StatInfo,String Hint);
  /** 析构函数 */
  __fastcall ~CStat(); 
       /**
       * 增加一个事件处理对象
       * @param NewTE           由用户创建的事件对象
       * @see AddTransitionEvent()
       * @return 添加成功返回 True,失败返回 False
       */
  bool __fastcall  AddTransitionEvent(CTransitionEvent *NewTE);     
         /**
       * 增加一个事件处理对象
       * @param EventID       事件ID,不能重复
       * @param BeforeEventAction  收到事件状态转变之 ”前“ 执行自定义函数指针
       * @param AfterAction   收到事件状态转变之 “后” 执行自定义函数指针
       * @param DesStauID     目标状态ID,此事件发生后导致转换到目标状态
       * @see AddTransitionEvent()
       * @return 添加成功返回 一个新的CTransitionEvent对象指针(由CStat负责释放,用户无需释放),失败返回 NULL
       */       
  CTransitionEvent *  __fastcall  AddTransitionEvent(int EventID,TFUN_EVENT_ACTION BeforeEventAction,TFUN_EVENT_ACTION AfterAction,int DesStauID);
        /**
       * 清空事件对象表
       */
  __inline void __fastcall ClearTransitionEvent(){TranstionList->Clear();}  
         /**
       * 返回此状态的事件对象数量
       * @see AddTransitionEvent()
       * @return 返回影响此状态所包含的事件对象数量
       */         
  __inline int __fastcall TECount(){return TranstionList->Count();}      
           /**
       * 根据所发生的事件执行转换动作,返回转换后的目标状态ID
       * @param EventID       触发事件ID,作为本次状态转换的源消息
       * @see AddTransitionEvent()
       * @return 返回转换后的新状态ID
       */    
  int __fastcall Transition(int EventID); 
           /**
       * 通知状态转换成功,执行状态结束代码
       * @see AddTransitionEvent()
       */    
  void __fastcall EventSuccess(int EventID);
             /**
       * 获取状态ID
       * @see GetImageIndex() 
       */    
  __inline int    GetID(){return _ID;}
       /**
       * 获取状态的图形索引编号
       * @see GetImageIndex() 
       */    
  __inline int    GetImageIndex(){return _ImageIndex;}
         /**
       * 获取状态的名字信息
       * @see GetImageIndex() GetInfo()
       */   
  __inline String GetInfo(){return _Info;}
         /**
       * 获取状态的详细说明信息
       * @see GetImageIndex() 
       */   
  __inline String GetHint(){return _Hint;}
};


/**事件转换通知回调函数指针定义*/
typedef void  __fastcall (__closure *TFUN_EVENT_CHANAGE)(CStat *OldStat,CStat *NewStat);
class CFSM_Manage//有限状态机类
{
private:
   AList<CStat> * StatList; //状态列表
   int _CurrentStatID; //当前状态ID
protected:
  int        GetStatIndex(int StatID);  //获取某事件处理对象的Index
  CStat *    GetStat(int StatID); //根据ID获取状态对象
public:
  __fastcall CFSM_Manage();
  __fastcall ~CFSM_Manage();
  __inline int __fastcall Count(){return StatList->Count();}  //所有状态的数量
 __inline void __fastcall ClearStat(){StatList->Clear();}  //清空状态表
 bool __fastcall  Add(CStat *NewStat); //增加一个状态对象
 CStat * Add(int StatID,int StatImageIndex,String StatInfo,String Hint);
 int __fastcall Transition(int EventID); //根据所发生的事件执行转换动作,返回转换后的目标状态ID
 __inline int __fastcall GetCurrentStatID(){return _CurrentStatID;}
 void __fastcall SetStat(int NewStatID);//强制设置当前的状态ID
 __inline CStat *    GetCurrentStat(){return  GetStat(_CurrentStatID);} //获取当前状态对象指针
 TFUN_EVENT_CHANAGE  OnStausChanage;
 void       RefreshGUI();
};

//---------------------------------------------------------------------------
#endif


 /** @}*/ // 有限状态机