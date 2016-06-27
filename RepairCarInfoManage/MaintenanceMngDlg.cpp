// MaintenanceMngDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RepairCarInfoManage.h"
#include "MaintenanceMngDlg.h"
#include "afxdialogex.h"


// CMaintenanceMngDlg 对话框

IMPLEMENT_DYNAMIC(CMaintenanceMngDlg, CDialog)

CMaintenanceMngDlg::CMaintenanceMngDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMaintenanceMngDlg::IDD, pParent)
{

}

CMaintenanceMngDlg::~CMaintenanceMngDlg()
{
}

void CMaintenanceMngDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMaintenanceMngDlg, CDialog)
END_MESSAGE_MAP()


// CMaintenanceMngDlg 消息处理程序
