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
	// ��Esc��Enter�����¼���Ϣ���˵����������Ϣ�ᵼ�¶�ӦӦ�ó������OnOK��������������Ӧ�ó���
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE: //Esc�����¼�
			return true;
		case VK_RETURN: //Enter�����¼�
			return true;
		default:
			;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
