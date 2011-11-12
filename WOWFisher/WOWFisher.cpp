//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("ChargeFrm.cpp", frmChargeFrm);
USEFORM("Main.cpp", WOWFisherMain);
USEFORM("..\WOWPacketReviewer\ValuesUpdateFrm.cpp", FrmValuesUpdate);
USEFORM("..\WOWPacketReviewer\DrawMapFrm.cpp", FrmDrawMap);
USEFORM("..\WOWPacketReviewer\DockFrm.cpp", frmDock);
USEFORM("..\WOWPacketReviewer\MapFrm.cpp", FrmMap);
USEFORM("..\WOWPacketReviewer\CommentFrm.cpp", FrmComment);
USEFORM("..\WOWPacketReviewer\GameDataViewerFrm.cpp", FrmGameDataViewer);
USEFORM("..\WOWPacketReviewer\WOWPacketReviewer.cpp", WOWReviewerMainFrm);
USEFORM("..\WOWPacketReviewer\BlockWindowFrm.cpp", frmBlock);
USEFORM("..\WOWPacketReviewer\DataViewerFrm.cpp", FrmDBCViewer);
USEFORM("AutoChatFrm.cpp", FrmAutoChat);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TWOWFisherMain), &WOWFisherMain);
		Application->CreateForm(__classid(TfrmChargeFrm), &frmChargeFrm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
