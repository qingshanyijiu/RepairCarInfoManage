// UserMngDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RepairCarInfoManage.h"
#include "UserMngDlg.h"
#include "afxdialogex.h"


// CUserMngDlg 对话框

IMPLEMENT_DYNAMIC(CUserMngDlg, CDialog)

CUserMngDlg::CUserMngDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserMngDlg::IDD, pParent)
{

}

CUserMngDlg::~CUserMngDlg()
{
}

void CUserMngDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserMngDlg, CDialog)
END_MESSAGE_MAP()


// CUserMngDlg 消息处理程序
