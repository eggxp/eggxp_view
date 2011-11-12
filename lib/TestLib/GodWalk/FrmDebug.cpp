//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FrmDebug.h"
#include "ChCommon.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "Commfunc.h"
TDebugFrm *DebugFrm;

#define     DEBUG_MAX_LINE_COUNT        100000
//---------------------------------------------------------------------------
__fastcall TDebugFrm::TDebugFrm(TComponent* Owner)
	: TForm(Owner)
{
	m_iCount = 0;
	m_iTag = 0;
}
//---------------------------------------------------------------------------

void		TDebugFrm::AddSend(String data)
{
	String strData = BinToStr(data.c_str() ,data.Length());
	if(cbEnableDebug->Checked)
		AddData(memSend, memUnShowSend, strData, "Send");
}

void		TDebugFrm::AddRecv(String data)
{
	String strData = BinToStr(data.c_str() ,data.Length());
	if(cbEnableDebug->Checked)
		AddData(memRecv, memUnShowRecv, strData, "Recv");
}

void		TDebugFrm::AddData(TMemo * mem, TMemo * unShow, String data, String fileName)
{
	int pos;
	
	if(cbUnShow->Checked)
	{
		if(cbDisUnShow->Checked == false)
		{
			for(int i=0; i<unShow->Lines->Count; i++)
			{
				pos = data.AnsiPos(unShow->Lines->Strings[i]);
				if(pos == 1)
					return;
			}
		}
		else
		{
			bool canShow = false;
			for(int i=0; i<unShow->Lines->Count; i++)
			{
				pos = data.AnsiPos(unShow->Lines->Strings[i]);

				if(pos == 1)
				{
					canShow = true;
				}
			}
			if(canShow == false)
				return;
		}

	}

	if(mem->Lines->Count >= DEBUG_MAX_LINE_COUNT)
	{
		mem->Lines->Clear();
	}
	
	mem->Lines->Add(FormatStr("[#%d %s] : %s", m_iCount, Now().TimeString(), data));


	//All
	if(memAll->Lines->Count >= DEBUG_MAX_LINE_COUNT*2)
	{
		memAll->Lines->Clear();
	}
	memAll->Lines->Add(FormatStr("[%s][#%d %s] : %s", fileName, m_iCount, Now().TimeString(), data));

	m_iCount++;
}
void __fastcall TDebugFrm::btClearClick(TObject *Sender)
{
	memSend->Clear();
	memRecv->Clear();
	memAll->Clear();
}
//---------------------------------------------------------------------------
void		TDebugFrm::SaveDebug(String path)
{
	memSend->Lines->SaveToFile(path + "Send.txt");
	memRecv->Lines->SaveToFile(path + "Recv.txt");
	memAll->Lines->SaveToFile(path + "AllSendRecv.txt");
}
//---------------------------------------------------------------------------
void __fastcall TDebugFrm::Button1Click(TObject *Sender)
{
	 char Buffer[8192];
	 int Len = WY_HexToBin(edtVRecvData->Text.c_str(),Buffer,sizeof(Buffer));
	 if (Len<4)
	 {
	   //³¤¶È²»×ã
	   return ;
	 }
}
//---------------------------------------------------------------------------

