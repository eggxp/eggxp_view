//---------------------------------------------------------------------------

#include <memory>
#pragma hdrstop
#include "CommFunc.h"
#include "ShareDef.h"
#include "Log4Me.h"

using namespace std;

//---------------------------------------------------------------------------

#pragma package(smart_init)

#define		TAG_FORM_CLASSNAME		"GxWindowClassD3d"
static	String	gTagFormClassName;
static	String  gTagFormCaptionName;

void  SetTagFormClassName(String clsName, String capName)
{
	gTagFormClassName = clsName;
	gTagFormCaptionName = capName;
}

bool	IsTagFormClassName(String clsName, String capName)
{
	if(clsName == TAG_FORM_CLASSNAME)
	{
		return true;
	}
	if(gTagFormClassName == "")
	{
		return false;
	}
	if(clsName != gTagFormClassName)
	{
		return false;
	}
	if (gTagFormCaptionName == "")
	{
		return true;
	}
	if (gTagFormCaptionName != capName)
	{
		return false;
	}
	return true;
}

#if defined(WOW_FISHER) && !defined(_DEBUG)
#else
static const int gAddr_Table_Size = sizeof(gAddr_Table) / (3 * 4);

bool FindAddrInfo(int build, tagWOWAddrInfo *result)
{
	for(int i=0; i<gAddr_Table_Size; i++)
	{
		if(gAddr_Table[i][0] == build)
		{
			result->Build = gAddr_Table[i][0];
			result->Addr = gAddr_Table[i][1];
			result->Offset = gAddr_Table[i][2];
			return true;
		}
	}

	String fileName = "SessionInfo.txt";
	if (FileExists(fileName))
	{
		auto_ptr<TStringList> loadStr(new TStringList);
		auto_ptr<TStringList> splitStr(new TStringList);
		loadStr->LoadFromFile(fileName);
		for (int i=0; i<loadStr->Count; i++)
		{
			SplitStr(loadStr->Strings[i], " ", splitStr.get());
			if (splitStr->Count != 3)
			{
				GetLog()->Warn(FormatStr("%s Not Right", loadStr->Strings[i]));
				continue;
			}
			int readBuild = splitStr->Strings[0].ToIntDef(0);
			if(readBuild != build)
			{
				continue;
			}
			result->Build = readBuild;
			result->Addr = splitStr->Strings[1].ToIntDef(0);
			result->Offset = splitStr->Strings[2].ToIntDef(0);
			return true;
		}
	}
	return false;
}
#endif

String		GBText(String text)
{
	return	text;
}
