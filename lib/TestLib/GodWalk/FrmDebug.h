//---------------------------------------------------------------------------

#ifndef FrmDebugH
#define FrmDebugH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TDebugFrm : public TForm
{
__published:
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TMemo *memSend;
	TMemo *memRecv;
	TCheckBox *cbEnableDebug;
	TSplitter *Splitter1;
	TPageControl *PageControl2;
	TTabSheet *TabSheet3;
	TTabSheet *TabSheet4;
	TMemo *memUnShowSend;
	TMemo *memUnShowRecv;
	TTabSheet *TabSheet5;
	TMemo *memAll;
	TButton *btClear;
	TCheckBox *cbUnShow;
	TCheckBox *cbDisUnShow;
	TTabSheet *TabSheet6;
	TLabel *Label1;
	TEdit *edtVRecvData;
	TButton *Button1;
	void __fastcall btClearClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
	void		AddData(TMemo * mem, TMemo * unShow, String data, String fileName);
	DWORD		m_iCount;
	int			m_iTag;
public:		// User declarations
	__fastcall TDebugFrm(TComponent* Owner);
	void		AddSend(String data);
	void		AddRecv(String data);
	void		SaveDebug(String path);
};
//---------------------------------------------------------------------------
extern PACKAGE TDebugFrm *DebugFrm;
//---------------------------------------------------------------------------
#endif
