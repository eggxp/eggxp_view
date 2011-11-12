//---------------------------------------------------------------------------

#ifndef wybarH
#define wybarH
#include <vcl.h>
enum TextShowStyle{tssVALUE,tssPERCENT,tssBOTH,tssNONE};
//文本风格,数值,百分比,两者一起显示,两者都不显示
class WYDrawBar
{
private:
  TPaintBox * OwnPaintBox;
protected:
   int	Min;
   int  Max;
   int  Position;
   TColor  m_TextColor;//文本颜色
   TColor  m_BarColor; //进度条颜色
   TColor  m_BGColor;  //背景色
   TColor  m_FrameLineColor;//框线颜色
   bool    m_ShowFrameLine; //是否显示框线
   TextShowStyle  m_TextStyle;
   String	CurTextHead;
   void Refresh();
   void __fastcall OnPaint(System::TObject* Sender);
   void SetMin(int Value);
   void Init();
public:
   WYDrawBar(TPaintBox * PaintBox);
   WYDrawBar();
   ~WYDrawBar();
   void Bind(TPaintBox * PaintBox);
   void SetMax(int Value);
   void SetPosition(int Value,String NewText=" ");
   void SetTextColor(TColor TextColor);//文本颜色
   void SetBarColor(TColor  BarColor); //进度条颜色
   void SetFrameLineColor(TColor  FrameLineColor);//框线颜色
   void SetShowFrameLine(bool    ShowFrameLine); //是否显示框线
   void SetBGColor(TColor    BGColor);     //进度条背景色
   void SetTextStyle(TextShowStyle  TextStyle);  //文本显示方式

};
//---------------------------------------------------------------------------
#endif
