//---------------------------------------------------------------------------


#pragma hdrstop

#include "WYProfileView.h"
#include "WYProfile.h"
#include "commfunc.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

void AddTreeNode(TTreeView *TreeView1,TTreeNode* PNode,CProfileNode * ViewChildNode)
{
	CProfileNode * CurrentViewChildNode;
	TTreeNode* CurrentNode ;
	for (int i = 0; i < ViewChildNode->ChildCount() ; i++)
	{
		CurrentViewChildNode =  ViewChildNode->GetChildByIndex(i);
		CurrentNode = TreeView1->Items->AddChild(PNode,FormatStr("%s - 耗时:%f - 次数:%d - 占用率: %0.2f%",CurrentViewChildNode->GetName(),CurrentViewChildNode->GetCountValue(),CurrentViewChildNode->GetCountTimes(),CurrentViewChildNode->GetPercent()));
		AddTreeNode(TreeView1,CurrentNode,CurrentViewChildNode);
	}
}

void    OutputView(TTreeView *TreeView1,CProfileManager * ProfileMgr)
{
    TTreeNode* Root = TreeView1->Items->AddChild(NULL, ProfileMgr->GetName());
    CProfileNode * ViewNode = ProfileMgr->GetSelecttViewNode();
    AddTreeNode(TreeView1,Root,ViewNode);
    Root->Expand(true);
}


void	ViewProfileToTreeView(TTreeView *TreeView1,CProfileManager * ProfileMgr)
{
    TreeView1->Items->Clear();
    OutputView(TreeView1, ProfileMgr);
}

void	ViewThreadProfileToTreeView(TTreeView *TreeView1,CThreadProfileManager * ProfileMgr)
{
    OutputView(TreeView1, ProfileMgr);
}
