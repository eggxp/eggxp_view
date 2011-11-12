//---------------------------------------------------------------------------

#ifndef onpainttextH
#define onpainttextH
#include <vcl.h>
typedef String __fastcall (__closure *TOnGetText)(int Index);
class WYPaintTextList
{
private:
   TPaintBox * OutputPaintBox;
protected:
   int m_Height;
   int m_Count;
   bool m_IsActive;
   Classes::TNotifyEvent OldOnPaint;
   void __fastcall OnPaint(System::TObject* Sender);
   void Init();
public:
	WYPaintTextList(TPaintBox * PaintBox);
	WYPaintTextList();
	~WYPaintTextList();
	void Bind(TPaintBox * PaintBox);
	void SetHeight(int Height);
	void SetActive(bool IsActive);
	void Refresh(int Count);
	TOnGetText   OnGetText;
};
//---------------------------------------------------------------------------
#endif
