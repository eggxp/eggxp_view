//---------------------------------------------------------------------------

#include <memory>
#include <vcl.h>
#pragma hdrstop

using namespace std;

#include "PackerMain.h"
#include "ShareDef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void PackFile(String path)
{
	String exeName = path + "WOWFisher.exe";
	String dllName = path + "wowgo.dll";

	if(!FileExists(exeName))
	{
		ShowMessage("exe Not Exist!");
		return;
	}

	if(!FileExists(dllName))
	{
		ShowMessage("dll Not Exist!");
		return;
	}

	auto_ptr<TMemoryStream> exeStream(new TMemoryStream);
	exeStream->LoadFromFile(exeName);

	auto_ptr<TMemoryStream> dllStream(new TMemoryStream);
	dllStream->LoadFromFile(dllName);

	auto_ptr<TMemoryStream> allStream(new TMemoryStream);
	allStream->Size = exeStream->Size + dllStream->Size + sizeof(int) + 4;
    memset(allStream->Memory, 0, allStream->Size);

	allStream->Position = 0;
	allStream->Write(exeStream->Memory, exeStream->Size);

	allStream->Position = exeStream->Size;
	allStream->Write(dllStream->Memory, dllStream->Size);

	allStream->Position = exeStream->Size + dllStream->Size;
	int dllSize = dllStream->Size;
	allStream->Write(&dllSize, sizeof(int));

	allStream->Position = exeStream->Size + dllStream->Size + sizeof(int);
	AnsiString wow = PACKER_MAGIC;
	allStream->Write(wow.c_str(), wow.Length());

	allStream->SaveToFile(path + "GoldFish.exe");
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	String path = ExtractFilePath(Application->ExeName);
	PackFile(path + "BinDebug\\");
	PackFile(path + "BinRelease\\");
	Application->Terminate();
}
//---------------------------------------------------------------------------
