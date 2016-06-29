// RepairInfoQueryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RepairCarInfoManage.h"
#include "RepairInfoQueryDlg.h"
#include "afxdialogex.h"


// CRepairInfoQueryDlg dialog

IMPLEMENT_DYNAMIC(CRepairInfoQueryDlg, CDialogEx)

CRepairInfoQueryDlg::CRepairInfoQueryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRepairInfoQueryDlg::IDD, pParent)
{

}

CRepairInfoQueryDlg::~CRepairInfoQueryDlg()
{
}

void CRepairInfoQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRepairInfoQueryDlg, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_RepairList, &CRepairInfoQueryDlg::OnRclickListRepairlist)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RepairList, &CRepairInfoQueryDlg::OnDblclkListRepairlist)
	ON_COMMAND(ID_SMENU_RepairDelete, &CRepairInfoQueryDlg::OnSmenuRepairdelete)
	ON_COMMAND(ID_SMENU_RepairDetail, &CRepairInfoQueryDlg::OnSmenuRepairdetail)
	ON_COMMAND(ID_SMENU_RepairModify, &CRepairInfoQueryDlg::OnSmenuRepairmodify)
	ON_COMMAND(ID_SMENU_RepairQueryUser, &CRepairInfoQueryDlg::OnSmenuRepairqueryuser)
END_MESSAGE_MAP()


// CRepairInfoQueryDlg message handlers


void CRepairInfoQueryDlg::OnRclickListRepairlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//if(pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU_RepairMenu ) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
	}
	*pResult = 0;
}


void CRepairInfoQueryDlg::OnDblclkListRepairlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	

	*pResult = 0;
}


void CRepairInfoQueryDlg::OnSmenuRepairdelete()
{
	// TODO: Add your command handler code here
}


void CRepairInfoQueryDlg::OnSmenuRepairdetail()
{
	// TODO: Add your command handler code here
}


void CRepairInfoQueryDlg::OnSmenuRepairmodify()
{
	// TODO: Add your command handler code here
}


void CRepairInfoQueryDlg::OnSmenuRepairqueryuser()
{
	// TODO: Add your command handler code here
}


BOOL CRepairInfoQueryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
