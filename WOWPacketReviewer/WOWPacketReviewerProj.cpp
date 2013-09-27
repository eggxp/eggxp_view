//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

//---------------------------------------------------------------------------
USEFORM("MapFrm.cpp", FrmMap);
USEFORM("ValuesUpdateFrm.cpp", FrmValuesUpdate);
USEFORM("DockFrm.cpp", frmDock);
USEFORM("DrawMapFrm.cpp", FrmDrawMap);
USEFORM("WOWPacketReviewer.cpp", WOWReviewerMainFrm);
USEFORM("GameDataViewerFrm.cpp", FrmGameDataViewer);
USEFORM("CommentFrm.cpp", FrmComment);
USEFORM("BlockWindowFrm.cpp", frmBlock);
USEFORM("DataViewerFrm.cpp", FrmDBCViewer);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TWOWReviewerMainFrm), &WOWReviewerMainFrm);
		Application->CreateForm(__classid(TfrmBlock), &frmBlock);
		Application->CreateForm(__classid(TFrmComment), &FrmComment);
		Application->CreateForm(__classid(TFrmMap), &FrmMap);
		Application->CreateForm(__classid(TFrmDBCViewer), &FrmDBCViewer);
		Application->CreateForm(__classid(TFrmGameDataViewer), &FrmGameDataViewer);
		Application->CreateForm(__classid(TFrmValuesUpdate), &FrmValuesUpdate);
		Application->CreateForm(__classid(TFrmDrawMap), &FrmDrawMap);
		Application->CreateForm(__classid(TfrmDock), &frmDock);
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
