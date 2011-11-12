//---------------------------------------------------------------------------

#ifndef panpageH
#define panpageH
#include <vcl.h>
#define REVISE_OFFSET 15
#define HINT_SHOW_DELAY 2000   //提示显示时间,2000ms
typedef void __fastcall (__closure *TONPageChanage)(int ActivePage);
//---------------------------------------------------------------------------
class TPanelPage
{
private:
   TPaintBox   *  m_lpParentPanel;
   TStringList *  m_lpPageList;
   TImageList  *  m_lpImageList;
   TImage      *  m_ActivePageImage;
   TImage      *  m_NormalPageImage;
   TImage      *  m_HotPageImage;
   THintWindow  * m_HintWindow;
   TTimer       * m_HintTimer;
   bool           MouseTrack;
   Classes::TWndMethod  m_fpOrgParentWndProc;
   DWORD            HintHideTime;
protected:
   int  m_ActiveIndex;
   int  m_HotIndex;//鼠标所在的Index
   void __fastcall SubWinMsgProc(Messages::TMessage &Message);
   void __fastcall OnPaint(System::TObject* Sender);
   void __fastcall OnHintTimer(System::TObject* Sender);
   void __fastcall OnMouseMove(TObject *Sender,TShiftState Shift, int X, int Y);
   void __fastcall OnMouseUp(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y);
public:
  __fastcall TPanelPage(TPaintBox *ParentPanel);
  __fastcall ~TPanelPage();
  __inline   void SetImageList(TImageList *ImageList){m_lpImageList = ImageList;}
  __inline   void SetPageImage(TImage *ActivePageImage,TImage  * NormalPageImage){m_ActivePageImage = ActivePageImage;m_NormalPageImage = NormalPageImage;}
  __inline   void SetHotPageImage(TImage *HotPageImage){m_HotPageImage = HotPageImage;}
  void       Add(const String &PageName);
  void       Delete(int Index);
  __inline   int ActiveIndex(){return m_ActiveIndex;}
  void       Refresh(){m_lpParentPanel->Repaint();}
  bool       SetActiveIndex(int Index);
  __inline   bool  SetActiveIndex(const String &PageName){return SetActiveIndex(GetPageIndex(PageName));}
  int        GetPageIndex(const String &PageName);
  String     GetActive(int Index);
  String     GetActivePageName();

  TONPageChanage OnChanage;


};

#endif
