//---------------------------------------------------------------------------
#pragma hdrstop

#include "panpage.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//------------------------------------------------------------------------------
__fastcall TPanelPage::TPanelPage(TPaintBox *ParentPanel)
{
   m_lpParentPanel = ParentPanel;
   m_lpPageList    = new TStringList;
   m_ActiveIndex = -1;
   m_lpImageList = NULL;
   m_ActivePageImage = NULL;
   m_NormalPageImage = NULL;
   m_HotPageImage    = NULL;
   OnChanage         = NULL;
   m_lpParentPanel->OnPaint  = OnPaint;
   m_lpParentPanel->OnMouseUp = OnMouseUp;
   m_lpParentPanel->OnMouseMove = OnMouseMove;
   m_lpParentPanel->Parent->DoubleBuffered = true;
   m_HotIndex = -1;
   m_HintWindow = new THintWindow(ParentPanel);
   m_HintWindow->Color =   clInfoBk;
   m_HintTimer  = new TTimer(NULL);
   m_HintTimer->Interval = 300;
   m_HintTimer->Enabled  = false;
   m_HintTimer->OnTimer = OnHintTimer;
   MouseTrack = false;
  // m_fpOrgParentWndProc =   m_lpParentPanel->WindowProc;
   //m_lpParentPanel->WindowProc =  SubWinMsgProc;
   HintHideTime = 0;
}
//---------------------------------------------------------------------------
__fastcall TPanelPage::~TPanelPage()
{
   delete m_lpPageList;
   delete m_HintWindow;
   delete m_HintTimer;
}
//---------------------------------------------------------------------------
void __fastcall TPanelPage::SubWinMsgProc(Messages::TMessage &Message)
{
    if(Message.Msg == WM_MOUSELEAVE)    //在这里捕获WM_MOUSELEAVE消息
    {
        MouseTrack = false;             //鼠标Track已经完成
        m_HotIndex = -1;
    }
    else
      m_fpOrgParentWndProc(Message);
}
//---------------------------------------------------------------------------
void  TPanelPage::Add(const String &PageName)
{
    m_lpPageList->Add(PageName);
    m_ActiveIndex = m_lpPageList->Count-1;
}
//---------------------------------------------------------------------------
void  TPanelPage::Delete(int Index)
{
    if (Index>=0 && Index< m_lpPageList->Count)
    {
       m_lpPageList->Delete(Index);
       if (m_lpPageList->Count > 0)
       {
          m_ActiveIndex = 0;
       }
       else
       {
          m_ActiveIndex = -1;
       }
    }
}
//---------------------------------------------------------------------------
void __fastcall TPanelPage::OnPaint(System::TObject *Sender)
{
    if(m_ActivePageImage == NULL || m_NormalPageImage == NULL)
    {
        return;
    }

    int Y = 0;
    int ImageIndex = 0;

    // m_HotIndex =   m_lpMouse->CursorPos.y/(m_ActivePageImage->Height- REVISE_OFFSET);
    for(int i = m_lpPageList->Count - 1; i >= 0; i--)
    {
        if(i == 0)
        {
            Y = 0;
        }
        else
        {
            Y = i * (m_ActivePageImage->Height - REVISE_OFFSET);
        }

        ImageIndex = i;
        if(ImageIndex >= m_lpImageList->Count)
        {
            ImageIndex = 0;
        }

        if(i == m_ActiveIndex)  //激活窗口
        {
            m_lpParentPanel->Canvas->Draw(0, Y, m_ActivePageImage->Picture->Bitmap);
            m_lpImageList->Draw(m_lpParentPanel->Canvas, 2, Y + 5, ImageIndex, dsTransparent);
        }
        else
        {
            if(i == m_HotIndex)
            {
                m_lpParentPanel->Canvas->Draw(0, Y, m_HotPageImage->Picture->Bitmap);
            }
            else
            {
                m_lpParentPanel->Canvas->Draw(0, Y, m_NormalPageImage->Picture->Bitmap);
            }

            m_lpImageList->Draw(m_lpParentPanel->Canvas, 2, Y + 5, ImageIndex, dsTransparent);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TPanelPage::OnMouseUp(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{
    int Index =   Y /(m_ActivePageImage->Height- REVISE_OFFSET);
    if (SetActiveIndex(Index))
    {
      Refresh();
    }
}
//---------------------------------------------------------------------------
void __fastcall TPanelPage::OnMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    int Index =   Y /(m_ActivePageImage->Height- REVISE_OFFSET);
    if (Index>=0 && Index< m_lpPageList->Count)
    {
       if (Index != m_HotIndex)
       {
         m_lpParentPanel->Cursor =  crHandPoint; //当前处于有效页面,置光标为手形
         m_HintTimer->Enabled = false;
         m_HotIndex = Index;
         TRect HintRect;
         TPoint TempPT;
         HintRect = m_HintWindow->CalcHintRect(100,GetActive(Index),NULL);
         HintRect.Left   = HintRect.Left+m_lpParentPanel->ClientRect.right;
         HintRect.right  = HintRect.right+m_lpParentPanel->ClientRect.right;
         HintRect.top    = HintRect.top+Y;
         HintRect.Bottom = HintRect.Bottom+Y;
         TempPT = m_lpParentPanel->ClientToScreen(TPoint(HintRect.left,HintRect.top));
         HintRect.Left = TempPT.x;
         HintRect.top  = TempPT.y;
         TempPT = m_lpParentPanel->ClientToScreen(TPoint(HintRect.right,HintRect.Bottom));
         HintRect.right  = TempPT.x;
         HintRect.Bottom = TempPT.y;
         m_HintWindow->ActivateHint(HintRect,GetActive(Index));
         HintHideTime =  GetTickCount()+HINT_SHOW_DELAY;
         m_HintTimer->Enabled = true;
       }
    }
    else
    {
       m_lpParentPanel->Cursor =  crDefault;
       m_HotIndex = -1;
       m_HintWindow->ReleaseHandle();
    }
    Refresh();
}
//---------------------------------------------------------------------------
bool   TPanelPage::SetActiveIndex(int Index)
{
    if (Index >=0 && Index < m_lpPageList->Count)
    {
       m_ActiveIndex =  Index;
       Refresh();
      if (OnChanage!=NULL)
      {
        OnChanage(Index);
      }
       return true;
    }
    return false;
}
//---------------------------------------------------------------------------
String   TPanelPage::GetActive(int Index)
{
    if (Index >=0 && Index < m_lpPageList->Count)
    {
       return m_lpPageList->Strings[Index];
    }
    return "";
}
//---------------------------------------------------------------------------
String   TPanelPage::GetActivePageName()
{
	 return  GetActive(ActiveIndex());
}
//---------------------------------------------------------------------------
void __fastcall TPanelPage::OnHintTimer(System::TObject* Sender)
{
   if (HintHideTime!=0 && GetTickCount() > HintHideTime) //检查提示显示时间是否已经到了
   {
      m_HintWindow->ReleaseHandle();
      HintHideTime = 0;
   }
   TPoint MousePos;
   GetCursorPos(&MousePos);
   MousePos =  m_lpParentPanel->ScreenToClient(MousePos);
   if (!PtInRect(m_lpParentPanel->ClientRect,MousePos))    //鼠标已经移出了客户区
   {
       m_HotIndex = -1;
       m_HintTimer->Enabled = false;
       m_HintWindow->ReleaseHandle();
       HintHideTime = 0;
       Refresh();
   }
}
//---------------------------------------------------------------------------
int      TPanelPage::GetPageIndex(const String &PageName)
{
    for(int i=0;i<m_lpPageList->Count;i++)
    {
         if (m_lpPageList->Strings[i] ==  PageName)
         {
            return i;
         }
    }
    return -1;
}
