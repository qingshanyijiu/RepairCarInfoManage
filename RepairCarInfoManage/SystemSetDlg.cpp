// SystemSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RepairCarInfoManage.h"
#include "SystemSetDlg.h"
#include "afxdialogex.h"


// CSystemSetDlg dialog

IMPLEMENT_DYNAMIC(CSystemSetDlg, CDialogEx)

CSystemSetDlg::CSystemSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSystemSetDlg::IDD, pParent)
{

}

CSystemSetDlg::~CSystemSetDlg()
{
}

void CSystemSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSystemSetDlg, CDialogEx)
END_MESSAGE_MAP()


// CSystemSetDlg message handlers


BOOL CSystemSetDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	// 把Esc和Enter按键事件消息过滤掉，否则该消息会导致对应应用程序调用OnOK（）方法，结束应用程序
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE: //Esc按键事件
			return true;
		case VK_RETURN: //Enter按键事件
			return true;
		default:
			;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
