// UserInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RepairCarInfoManage.h"
#include "UserInfoDlg.h"
#include "afxdialogex.h"
#include "RepairCarInfoManageDlg.h"

extern CRepairCarInfoManageDlg*	g_pMainDlg;

// CUserInfoDlg dialog

IMPLEMENT_DYNAMIC(CUserInfoDlg, CDialogEx)

CUserInfoDlg::CUserInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserInfoDlg::IDD, pParent)
{
	m_bOperateType = OPERATE_TYPE_ADD;
	m_userInfo.Clear();
}

CUserInfoDlg::~CUserInfoDlg()
{
}

void CUserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_USER_ADD, m_addMotifyButton);
	DDX_Control(pDX, IDC_EDIT_userAddress, m_userAddreEdit);
	DDX_Control(pDX, IDC_EDIT_userLicNumber, m_userLicNumberEdit);
	DDX_Control(pDX, IDC_EDIT_userName, m_userNameEdit);
	DDX_Control(pDX, IDC_EDIT_userPhone, m_userPhoneEdit);
	DDX_Control(pDX, IDC_EDIT_userReserve, m_userReserveEdit);
}


BEGIN_MESSAGE_MAP(CUserInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_USER_ADD, &CUserInfoDlg::OnBnClickedBtnUserAdd)
END_MESSAGE_MAP()


// CUserInfoDlg message handlers


void CUserInfoDlg::OnBnClickedBtnUserAdd()
{
	// TODO: Add your control notification handler code here
	CString	strTemp;

	GetDlgItemText(IDC_EDIT_userLicNumber,strTemp);
	strncpy(m_userInfo.csLicenseNumber,strTemp.operator LPCSTR(),32);
	GetDlgItemText(IDC_EDIT_userName,strTemp);
	strncpy(m_userInfo.csUserName,strTemp.operator LPCSTR(),32);
	GetDlgItemText(IDC_EDIT_userPhone,strTemp);
	strncpy(m_userInfo.csUserPhone,strTemp.operator LPCSTR(),32);
	GetDlgItemText(IDC_EDIT_userAddress,strTemp);
	strncpy(m_userInfo.csUserAddress,strTemp.operator LPCSTR(),64);
	GetDlgItemText(IDC_EDIT_userReserve,strTemp);
	m_userInfo.strUserReserve = strTemp.operator LPCSTR();

	if (OPERATE_TYPE_ADD == m_bOperateType)
	{
		if(REPAIRCARINFOSAVEDB_SUCCESS ==InsertUserInfo(&m_userInfo))
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("插入车主信息成功！");
		}
		else
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("插入车主信息失败！可能是车牌信息冲突了！");
		}
	}
	else if (OPERATE_TYPE_MODIFY == m_bOperateType)
	{
		if(REPAIRCARINFOSAVEDB_SUCCESS ==UpdateUserInfo(&m_userInfo))
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("修改车主信息成功！");
		}
		else
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("修改车主信息失败！可能是无该记录！");
		}
	}
	else
	{
		g_pMainDlg->RightPageShow(IDD_USERMNG_QUERY_DLG);
	}
}


void CUserInfoDlg::SetOperateType(BYTE bType,PUserTableInfo pInfo/*=NULL*/)
{
	m_bOperateType = bType;
	m_userInfo.Clear();

	switch(bType)
	{
	case OPERATE_TYPE_ADD:
		{
			SetDlgItemText(IDC_EDIT_userLicNumber,"");
			SetDlgItemText(IDC_EDIT_userName,"");
			SetDlgItemText(IDC_EDIT_userPhone,"");
			SetDlgItemText(IDC_EDIT_userAddress,"");
			SetDlgItemText(IDC_EDIT_userReserve,"");

			m_addMotifyButton.SetWindowText("增加");
		}
		break;
	case OPERATE_TYPE_MODIFY:
	case OPERATE_TYPE_SHOW:

		SetDlgItemText(IDC_EDIT_userLicNumber,pInfo->csLicenseNumber);
		SetDlgItemText(IDC_EDIT_userName,pInfo->csUserName);
		SetDlgItemText(IDC_EDIT_userPhone,pInfo->csUserPhone);
		SetDlgItemText(IDC_EDIT_userAddress,pInfo->csUserAddress);
		SetDlgItemText(IDC_EDIT_userReserve,pInfo->strUserReserve.c_str());

		if(OPERATE_TYPE_MODIFY == m_bOperateType)
		{
			m_addMotifyButton.SetWindowText("修改");
		}
		else
		{
			m_addMotifyButton.SetWindowText("返回");
		}
		
		break;
	}
}

BOOL CUserInfoDlg::PreTranslateMessage(MSG* pMsg)
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


void CUserInfoDlg::PreInitDialog()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PreInitDialog();
}
