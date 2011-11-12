//---------------------------------------------------------------------------


#pragma hdrstop
#include <memory>
using namespace std;

#include "config.h"
#include "CommFunc.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
bool tagValueRecord::GUI2Value()
{
    bool Result=true;
    if (dynamic_cast<TEdit *>(GUIComponent) != NULL) // TEdit
    {
		TEdit   *EditValue = dynamic_cast<TEdit *>(GUIComponent);
		Value = EditValue->Text;
	}
    else if (dynamic_cast<TCSpinEdit *>(GUIComponent) != NULL)
    {
		TCSpinEdit  *EditValue = dynamic_cast<TCSpinEdit *>(GUIComponent);
        Value = EditValue->Value;
    }
    else if (dynamic_cast<TComboBox *>(GUIComponent) != NULL)
    {
        TComboBox   *EditValue = dynamic_cast<TComboBox *>
            (GUIComponent);
        Value = EditValue->ItemIndex;
    }
    else if (dynamic_cast<TCheckBox *>(GUIComponent) != NULL)
    {
        TCheckBox   *EditValue = dynamic_cast<TCheckBox *>
            (GUIComponent);
        Value = EditValue->Checked;
    }
    else if (dynamic_cast<TMemo *>(GUIComponent) != NULL)
    {
        TMemo   *EditValue = dynamic_cast<TMemo *>(GUIComponent);
        Value = EditValue->Text;
    }
    else
    {
        ShowMessage(FormatStr("Error On GUI2Value(),unknow GUIComponent %s,Name:%s",
                              String(GUIComponent->ClassName()),
                              GUIComponent->Name));
        Result = false;
    }
    return Result;
}

//---------------------------------------------------------------------------
bool tagValueRecord::Value2GUI()
{
    bool Result=true;
	if (dynamic_cast<TEdit *>(GUIComponent) != NULL)    // TEdit
    {
		TEdit   *EditValue = dynamic_cast<TEdit *>(GUIComponent);
		EditValue->Text = Value;
	}
    else if (dynamic_cast<TCSpinEdit *>(GUIComponent) != NULL)
    {
        TCSpinEdit  *EditValue = dynamic_cast<TCSpinEdit *>(GUIComponent);
        EditValue->Value = Value;
    }
    else if (dynamic_cast<TComboBox *>(GUIComponent) != NULL)
    {
        TComboBox   *EditValue = dynamic_cast<TComboBox *>(GUIComponent);
        EditValue->ItemIndex = Value;
    }
    else if (dynamic_cast<TCheckBox *>(GUIComponent) != NULL)
    {
        TCheckBox   *EditValue = dynamic_cast<TCheckBox *>(GUIComponent);
        EditValue->Checked = Value;
    }
    else if (dynamic_cast<TMemo *>(GUIComponent) != NULL)
    {
        TMemo   *EditValue = dynamic_cast<TMemo *>(GUIComponent);
        EditValue->Text = Value;
    }
    else
    {
        ShowMessage(FormatStr("Error On GUI2Value(),unknow GUIComponent %s,Name:%s",
                              String(GUIComponent->ClassName()),
                              GUIComponent->Name));
        Result = false;
    }
     return Result;
}
//---------------------------------------------------------------------------
bool  tagValueRecord::WriteToINI(TCustomIniFile *lpIniFile,const String &SecName)
{
    bool Result=true;
	if (dynamic_cast<TEdit *>(GUIComponent) != NULL)    // TEdit
    {
		TEdit   *EditValue = dynamic_cast<TEdit *>(GUIComponent);
		if (EditValue->PasswordChar != 0)  //非加密字段
		{
		   lpIniFile->WriteString(SecName,EditValue->Name,EncodeStr(Value));
		}
		else
		{
		   lpIniFile->WriteString(SecName,EditValue->Name,Value);
		}

    }
    else if (dynamic_cast<TCSpinEdit *>(GUIComponent) != NULL)
    {
        TCSpinEdit  *EditValue = dynamic_cast<TCSpinEdit *>(GUIComponent);
        lpIniFile->WriteInteger(SecName,EditValue->Name,Value);
    }
    else if (dynamic_cast<TComboBox *>(GUIComponent) != NULL)
    {
        TComboBox   *EditValue = dynamic_cast<TComboBox *>(GUIComponent);
        lpIniFile->WriteInteger(SecName,EditValue->Name,Value);
    }
    else if (dynamic_cast<TCheckBox *>(GUIComponent) != NULL)
    {
        TCheckBox   *EditValue = dynamic_cast<TCheckBox *>(GUIComponent);
        lpIniFile->WriteBool(SecName,EditValue->Name,Value);
    }
    else if (dynamic_cast<TMemo *>(GUIComponent) != NULL)
    {
        TMemo   *EditValue = dynamic_cast<TMemo *>(GUIComponent);
        lpIniFile->WriteString(SecName,EditValue->Name,Value);
    }
    else
    {
        ShowMessage(FormatStr("Error On GUI2Value(),unknow GUIComponent %s,Name:%s",
                              String(GUIComponent->ClassName()),
                              GUIComponent->Name));
        Result = false;
    }
     return Result;
}
//---------------------------------------------------------------------------
bool  tagValueRecord::ReadFromINI(TCustomIniFile *lpIniFile,const String &SecName)
{
    bool Result=true;
	if (dynamic_cast<TEdit *>(GUIComponent) != NULL)    // TEdit
	{
		TEdit   *EditValue = dynamic_cast<TEdit *>(GUIComponent);
		if (EditValue->PasswordChar != 0)  //非加密字段
		{
		   Value = DecodeStr(lpIniFile->ReadString(SecName,EditValue->Name,Value));
		}
		else
		{
		   Value = lpIniFile->ReadString(SecName,EditValue->Name,Value);
		}

    }
    else if (dynamic_cast<TCSpinEdit *>(GUIComponent) != NULL)
    {
        TCSpinEdit  *EditValue = dynamic_cast<TCSpinEdit *>(GUIComponent);
        Value = lpIniFile->ReadInteger(SecName,EditValue->Name,Value);
    }
    else if (dynamic_cast<TComboBox *>(GUIComponent) != NULL)
    {
        TComboBox   *EditValue = dynamic_cast<TComboBox *>(GUIComponent);
        Value = lpIniFile->ReadInteger(SecName,EditValue->Name,Value);
    }
    else if (dynamic_cast<TCheckBox *>(GUIComponent) != NULL)
    {
        TCheckBox   *EditValue = dynamic_cast<TCheckBox *>(GUIComponent);
        Value = lpIniFile->ReadBool(SecName,EditValue->Name,Value);
    }
    else if (dynamic_cast<TMemo *>(GUIComponent) != NULL)
    {
        TMemo   *EditValue = dynamic_cast<TMemo *>(GUIComponent);
        Value = lpIniFile->ReadString(SecName,EditValue->Name,Value);
    }
    else
    {
        ShowMessage(FormatStr("Error On GUI2Value(),unknow GUIComponent %s,Name:%s",
                              String(GUIComponent->ClassName()),
                              GUIComponent->Name));
        Result = false;
    }
     return Result;
}
//---------------------------------------------------------------------------
__fastcall TConfig::TConfig()
{
    m_lpCommonConfig = new AIndexList < tagValueRecord > (true);
}
//---------------------------------------------------------------------------
__fastcall TConfig::~TConfig()
{
    delete m_lpCommonConfig;
}
//---------------------------------------------------------------------------
void __fastcall TConfig::SetRecordName(const String &RecordName)
{
    m_RecordName =  RecordName;
}
//---------------------------------------------------------------------------
void __fastcall TConfig::AddOptionRecord(TComponent *GUI_Component)
{
    tagValueRecord  *NewRecord = m_lpCommonConfig->Find(GUI_Component->Name.c_str());
    if (NewRecord !=NULL) //已经存在,不能添加
    {
      return;
    }
    NewRecord = new tagValueRecord;
    NewRecord->GUIComponent = GUI_Component;
    if (NewRecord->GUI2Value())
    {
      m_lpCommonConfig->Add(GUI_Component->Name.c_str(), NewRecord);
      //m_lpCommonConfig->Add(GUI_Component->Name,NewRecord);
    }
}
//---------------------------------------------------------------------------
void __fastcall TConfig::GUI2Value()
{
    tagValueRecord  *NewRecord;
    for(int i = 0; i < m_lpCommonConfig->Count(); i++)
    {
        NewRecord = m_lpCommonConfig->At(i);
        NewRecord->GUI2Value();
    }
}
//---------------------------------------------------------------------------
void __fastcall TConfig::Value2GUI()
{
    tagValueRecord  *NewRecord;
    for(int i = 0; i < m_lpCommonConfig->Count(); i++)
    {
        NewRecord = m_lpCommonConfig->At(i);
        NewRecord->Value2GUI();
    }
}
//---------------------------------------------------------------------------
bool __fastcall IsNumber(Variant Value)
{

    /*
    varSmallint	0x0002	16-bit signed integer (type short int)
    varInteger	0x0003	32-bit signed integer (type int).
    varSingle	0x0004	Single-precision floating-point value (type float)
    varDouble	0x0005	Double-precision floating-point value (type double).
    varCurrency	0x0006	Currency floating-point value (type Currency).
    varDate	        0x0007	Date and time value (type TDateTime).
    */
    int Type = Value.Type();
    return (Type >= 0x2 && Type <= 0x7);
}
//---------------------------------------------------------------------------
bool __fastcall TConfig::Less(const String &OptionName, Variant Value)
{
    tagValueRecord  *NewRecord = m_lpCommonConfig->Find(OptionName.c_str());    //小于比较
    if(NewRecord == NULL || !IsNumber(NewRecord->Value) ||  !IsNumber(Value))
        return false;
    return (NewRecord->Value < Value);
}

//---------------------------------------------------------------------------
bool __fastcall TConfig::Same(const String &OptionName, Variant Value)
{
    tagValueRecord  *NewRecord = m_lpCommonConfig->Find(OptionName.c_str());
    if(NewRecord == NULL || !IsNumber(NewRecord->Value) ||  !IsNumber(Value))
        return false;
    return (NewRecord->Value == Value);
}

//---------------------------------------------------------------------------
bool __fastcall TConfig::Greater(const String &OptionName, Variant Value)
{
    tagValueRecord  *NewRecord = m_lpCommonConfig->Find(OptionName.c_str());
    if(NewRecord == NULL || !IsNumber(NewRecord->Value) ||  !IsNumber(Value))
        return false;
    return (NewRecord->Value > Value);
}

//---------------------------------------------------------------------------
bool __fastcall TConfig::LessAndSame(const String &OptionName, Variant Value)
{
    tagValueRecord  *NewRecord = m_lpCommonConfig->Find(OptionName.c_str());
    if(NewRecord == NULL || !IsNumber(NewRecord->Value) ||  !IsNumber(Value))
        return false;
    return (NewRecord->Value <= Value);
}

//---------------------------------------------------------------------------
bool __fastcall TConfig::GreaterAndSame(const String &OptionName, Variant Value)
{
    tagValueRecord  *NewRecord = m_lpCommonConfig->Find(OptionName.c_str());
    if(NewRecord == NULL || !IsNumber(NewRecord->Value) ||  !IsNumber(Value))
        return false;
    return (NewRecord->Value >= Value);
}
//---------------------------------------------------------------------------
bool TConfig::LoadFromFile(const String &FileName,const String &SecName)
{
   if (!FileExists(FileName))
   {
      return false;
   }

   auto_ptr<TMemIniFile> IniFile(new TMemIniFile(FileName));
   LoadFromIni(IniFile.get(),SecName);
   return true;

}
//---------------------------------------------------------------------------
void TConfig::SaveToFile(const String &FileName)
{
   auto_ptr<TMemIniFile> IniFile(new TMemIniFile(FileName));
   SaveToIni(IniFile.get());
}
//------------------------------------------------------------------------------
bool    TConfig::LoadFromIni(TMemIniFile * IniFile,const String &SecName)
{
    tagValueRecord  *NewRecord;
    for(int i=0;i<m_lpCommonConfig->Count();i++)
    {
        NewRecord =  m_lpCommonConfig->At(i);
        NewRecord->ReadFromINI(IniFile,SecName);
    }
    return true;
}
//------------------------------------------------------------------------------
void    TConfig::SaveToIni(TMemIniFile * IniFile)
{
	tagValueRecord  *NewRecord;
	if (m_RecordName =="")
	{
       return; 
	}
    for(int i=0;i<m_lpCommonConfig->Count();i++)
    {
        NewRecord =  m_lpCommonConfig->At(i);
        NewRecord->WriteToINI(IniFile,m_RecordName);
    }
    IniFile->UpdateFile();
}
//---------------------------------------------------------------------------
void __fastcall TConfig::SetValue(const String &OptionName,Variant Value)
{
    tagValueRecord  *NewRecord = m_lpCommonConfig->Find(OptionName.c_str());
    if(NewRecord == NULL)
        return ;
    NewRecord->Value = Value;
}
//---------------------------------------------------------------------------
Variant __fastcall TConfig::GetValue(const String &OptionName)
{
    tagValueRecord  *NewRecord = m_lpCommonConfig->Find(OptionName.c_str());
    if(NewRecord == NULL)
        return 0;
    return NewRecord->Value;
}

