// UserMngQueryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RepairCarInfoManage.h"
#include "UserMngQueryDlg.h"
#include "afxdialogex.h"


// CUserMngQueryDlg 对话框

IMPLEMENT_DYNAMIC(CUserMngQueryDlg, CDialog)

CUserMngQueryDlg::CUserMngQueryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserMngQueryDlg::IDD, pParent)
{

}

CUserMngQueryDlg::~CUserMngQueryDlg()
{
}

void CUserMngQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_GROUPBOX_USERQUEY, m_groupbox);
}


BEGIN_MESSAGE_MAP(CUserMngQueryDlg, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CUserMngQueryDlg 消息处理程序


void CUserMngQueryDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	CRect rc;
	GetWindowRect(&rc);
}
