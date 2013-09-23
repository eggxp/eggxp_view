//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ValuesUpdateFrm.h"
#include "CommentFrm.h"
#include "AuthLoader.h"
#include "CommFunc.h"
#include "Log4Me.h"
#include "CommPlus.h"
#include "ShareDef.h"
#include "BlockWindowFrm.h"
#include "FiberContext.h"
#include "KOEItlbm.h"
#include "FiberCode.h"
#include "MapFrm.h"
#include "DBCStructureInfo.h"
#include "DataViewerFrm.h"
#include "SharedMemInfo.h"
#include "ByteBuffer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmValuesUpdate *FrmValuesUpdate;



//---------------------------------------------------------------------------
__fastcall TFrmValuesUpdate::TFrmValuesUpdate(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmValuesUpdate::FormCreate(TObject *Sender)
{
	cbPackHead->Items->Add("SMSG_UPDATE_OBJECT");
	cbPackHead->Items->Add("SMSG_COMPRESSED_UPDATE_OBJECT");
	cbPackHead->ItemIndex = 0;
	m_CurBlockIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TFrmValuesUpdate::btPackInputClick(TObject *Sender)
{
	TReplaceFlags   flag;
	flag << rfReplaceAll;
	String data = StringReplace(edtPack->Text, "\r", "", flag);
    data = StringReplace(data, "\n", "", flag);
	data = StringReplace(data, "\"", "", flag);
	edtPack->Text = data;
	AnsiString packContent = HexStrToBinStr(data);

	m_WOWPackage.Clear();
	GetPackageFromDataPack(&m_WOWPackage, cbPackHead->Text.Trim(), RECV_MARK, packContent);
	Parse();
}
//---------------------------------------------------------------------------
void			TFrmValuesUpdate::Parse()
{
	GetGameWorld()->HandlerPacket(&m_WOWPackage);
	m_ValueResult = GetGameWorld()->GetGameObjectHandler()->GetUpdateValueResults();
	memComment->Text = m_WOWPackage.GetComment()->Text;
	RefreshUI();
}

void			TFrmValuesUpdate::BuidlValues(tagUpdateObjectValuesResult *input)
{
//	if(input->MaskSize == 0)
//		return;
//
//	if(input->MaskPos > m_WOWPackage.GetContentLen())
//	{
//		ShowMessage(FormatStr("未知错误?input->MaskPos(%d) > m_WOWPackage.GetContentLen(%d)", input->MaskPos, m_WOWPackage.GetContentLen()));
//		return;
//	}
//	ByteBuffer  buf;
//	buf.append((BYTE *)m_WOWPackage.GetHead(), m_WOWPackage.GetHeadSize());
//	buf.append((BYTE *)m_WOWPackage.GetContent(), input->MaskPos);
//	vector<BYTE> mask;
//	mask.resize(input->MaskSize);
//	for(DWORD i=0; i<input->Values.size(); i++)
//	{
//		WriteBit(&mask[0], mask.size(), input->Values[i].Type, 1);
//	}
//	buf.append(&mask[0], mask.size());
//	sort(input->Values.begin(), input->Values.end());
//	for(DWORD i=0; i<input->Values.size(); i++)
//	{
//		buf << (uint32)input->Values[i].Value;
//	}
//	buf.append((BYTE *)m_WOWPackage.GetContent() + input->ValuePosEnd, m_WOWPackage.GetContentLen() - input->ValuePosEnd);
//	m_WOWPackage.SetData(AnsiString((char *)buf.contents(), buf.size()));
//	m_WOWPackage.SetOpCode(SMSG_UPDATE_OBJECT);
//	m_WOWPackage.SetOpCodeMsg("SMSG_UPDATE_OBJECT");
//	m_WOWPackage.SetDecompress("");
}

void __fastcall TFrmValuesUpdate::btPackOutputClick(TObject *Sender)
{
	for (DWORD i=0; i<m_ValueResult.size(); i++)
	{
		BuidlValues(&m_ValueResult[i]);
	}
	ParseStart(&m_WOWPackage);

	cbPackHead->ItemIndex = 0;
	edtPack->Lines->Text = BinToStr(m_WOWPackage.GetContent(), m_WOWPackage.GetContentLen());
}
//---------------------------------------------------------------------------

void				TFrmValuesUpdate::RefreshUI()
{
	ListView_SetItemCountEx(lvBlocks->Handle, m_ValueResult.size(), LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
	lvBlocks->Refresh();

	RefreshBlocks();
}

void			TFrmValuesUpdate::RefreshBlocks()
{
	if (m_CurBlockIndex < 0 || m_CurBlockIndex >= (int)m_ValueResult.size())
	{
		return;
	}

	vector<tagUpdateObjectValueResult> *pValue = &m_ValueResult[m_CurBlockIndex].Values;
	sort(pValue->begin(), pValue->end());
	int cnt = m_ValueResult[m_CurBlockIndex].Values.size();
	ListView_SetItemCountEx(lvValues->Handle, cnt, LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
	lvValues->Refresh();
}

void __fastcall TFrmValuesUpdate::lvBlocksClick(TObject *Sender)
{
	if (lvBlocks->ItemIndex < 0 || lvBlocks->ItemIndex >= (int)m_ValueResult.size())
	{
		return;
	}
	m_CurBlockIndex = lvBlocks->ItemIndex;
	RefreshBlocks();
}
//---------------------------------------------------------------------------

void __fastcall TFrmValuesUpdate::lvBlocksData(TObject *Sender, TListItem *Item)
{
	if (Item->Index < 0 || Item->Index >= (int)m_ValueResult.size())
	{
		return;
	}

	tagUpdateObjectValuesResult *result = &m_ValueResult[Item->Index];
	Item->Caption = Item->Index;
	Item->SubItems->Add(result->BlockName);
	Item->SubItems->Add(result->ValuePosStart);
	Item->SubItems->Add(result->ValuePosEnd);
	Item->SubItems->Add(result->Values.size());
	Item->SubItems->Add(result->MaskPos);
	Item->SubItems->Add(result->MaskSize);
}
//---------------------------------------------------------------------------


void __fastcall TFrmValuesUpdate::lvValuesData(TObject *Sender, TListItem *Item)
{
	if (m_CurBlockIndex < 0 || m_CurBlockIndex >= (int)m_ValueResult.size())
	{
		return;
	}

	if (Item->Index < 0 || Item->Index >= (int)m_ValueResult[m_CurBlockIndex].Values.size())
	{
		return;
	}
	tagUpdateObjectValueResult *result = &m_ValueResult[m_CurBlockIndex].Values[Item->Index];
	int objTypeID = m_ValueResult[m_CurBlockIndex].ObjTypeID;
	Item->Caption = FindFieldName(objTypeID, result->Type);
	Item->SubItems->Add(GetDWORDInfo(objTypeID, result->Pos, (char *)&result->Value));
	Item->SubItems->Add(result->Pos);
}
//---------------------------------------------------------------------------

void				TFrmValuesUpdate::ParseStart(WOWPackage *input)
{
	m_WOWPackage.Assign(input);
	Parse();
	this->Show();
}
void __fastcall TFrmValuesUpdate::miWriteIntClick(TObject *Sender)
{
	if (m_CurBlockIndex < 0 || m_CurBlockIndex >= (int)m_ValueResult.size())
	{
		return;
	}

	String write = "0";
	if(!InputQuery("输入int", "输入int", write))
	{
		return;
	}
	int value = write.ToIntDef(0);
	for(int i=0; i<lvValues->Items->Count; i++)
	{
		if(lvValues->Items->Item[i]->Selected)
		{
			tagUpdateObjectValueResult *result = &m_ValueResult[m_CurBlockIndex].Values[i];
			result->Value = value;
		}
	}
	RefreshBlocks();
}
//---------------------------------------------------------------------------

void __fastcall TFrmValuesUpdate::miWriteFloatClick(TObject *Sender)
{
	if (m_CurBlockIndex < 0 || m_CurBlockIndex >= (int)m_ValueResult.size())
	{
		return;
	}

	String write = "0";
	if(!InputQuery("输入float", "输入float", write))
	{
		return;
	}

	float value = write.ToDouble();
	for(int i=0; i<lvValues->Items->Count; i++)
	{
		if(lvValues->Items->Item[i]->Selected)
		{
			tagUpdateObjectValueResult *result = &m_ValueResult[m_CurBlockIndex].Values[i];
			memcpy((char*)&result->Value, (char*)&value, sizeof(float));
		}
	}
	RefreshBlocks();
}
//---------------------------------------------------------------------------


void __fastcall TFrmValuesUpdate::miDeleteClick(TObject *Sender)
{
	if (m_CurBlockIndex < 0 || m_CurBlockIndex >= (int)m_ValueResult.size())
	{
		return;
	}

	vector<tagUpdateObjectValueResult> *vr = &m_ValueResult[m_CurBlockIndex].Values;
	for(int i=0; i<lvValues->Items->Count; i++)
	{
		if(lvValues->Items->Item[i]->Selected)
		{
			tagUpdateObjectValueResult *result = &vr->at(i);
			result->Type = -1;
		}
	}

	for (vector<tagUpdateObjectValueResult>::iterator it = vr->begin();
		it != vr->end();)
	{
		if(it->Type == -1)
		{
			it = vr->erase(it);
		}
		else
		{
			it++;
		}
	}
	RefreshBlocks();
	for(int i=0; i<lvValues->Items->Count; i++)
	{
		if(lvValues->Items->Item[i]->Selected)
		{
			lvValues->Items->Item[i]->Selected = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrmValuesUpdate::miAddValueClick(TObject *Sender)
{
	if (m_CurBlockIndex < 0 || m_CurBlockIndex >= (int)m_ValueResult.size())
	{
		return;
	}
	String write = "0";
	if(!InputQuery("输入index", "输入index", write))
	{
		return;
	}

	int index = write.ToIntDef(0);
	tagUpdateObjectValueResult ov;
	ov.Type = index;
	m_ValueResult[m_CurBlockIndex].Values.push_back(ov);
	RefreshBlocks();
}
//---------------------------------------------------------------------------



void __fastcall TFrmValuesUpdate::miChangeIndexClick(TObject *Sender)
{
	if (m_CurBlockIndex < 0 || m_CurBlockIndex >= (int)m_ValueResult.size())
	{
		return;
	}

	String write = "0";
	if(!InputQuery("输入index", "输入index", write))
	{
		return;
	}

	int index = write.ToIntDef(0);
	for(int i=0; i<lvValues->Items->Count; i++)
	{
		if(lvValues->Items->Item[i]->Selected)
		{
			tagUpdateObjectValueResult *result = &m_ValueResult[m_CurBlockIndex].Values[i];
			result->Type = index;
		}
	}
	RefreshBlocks();
}
//---------------------------------------------------------------------------

void __fastcall TFrmValuesUpdate::edtPackDblClick(TObject *Sender)
{
	edtPack->SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall TFrmValuesUpdate::miWriteByteClick(TObject *Sender)
{
	if (m_CurBlockIndex < 0 || m_CurBlockIndex >= (int)m_ValueResult.size())
	{
		return;
	}

	String write = "0";
	if(!InputQuery("输入bytes(空格分隔)", "输入bytes(空格分隔)", write))
	{
		return;
	}
	AnsiString data = HexStrToBinStr(write);
	if(data.Length() != (int)sizeof(int))
	{
		ShowMessage("Byte长度必须为4!");
		return;
	}
	for(int i=0; i<lvValues->Items->Count; i++)
	{
		if(lvValues->Items->Item[i]->Selected)
		{
			tagUpdateObjectValueResult *result = &m_ValueResult[m_CurBlockIndex].Values[i];
			memcpy((char*)&result->Value, data.c_str(), data.Length());
		}
	}
	RefreshBlocks();
}
//---------------------------------------------------------------------------

