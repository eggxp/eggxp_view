//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

//---------------------------------------------------------------------------
USEFORM("GameDataViewerFrm.cpp", FrmGameDataViewer);
USEFORM("MapFrm.cpp", FrmMap);
USEFORM("CommentFrm.cpp", FrmComment);
USEFORM("WOWPacketReviewer.cpp", WOWReviewerMainFrm);
USEFORM("BlockWindowFrm.cpp", frmBlock);
USEFORM("DataViewerFrm.cpp", FrmDBCViewer);
USEFORM("ValuesUpdateFrm.cpp", FrmValuesUpdate);
USEFORM("DrawMapFrm.cpp", FrmDrawMap);
USEFORM("DockFrm.cpp", frmDock);
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
