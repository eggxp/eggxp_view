//---------------------------------------------------------------------------

#ifndef WYProfileViewH
#define WYProfileViewH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>

class CProfileManager;
class CThreadProfileManager;

//---------------------------------------------------------------------------

void	ViewProfileToTreeView(TTreeView *TreeView1,CProfileManager * ProfileMgr);
void	ViewThreadProfileToTreeView(TTreeView *TreeView1,CThreadProfileManager * ProfileMgr);
#endif
