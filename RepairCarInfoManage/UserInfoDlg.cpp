// UserInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RepairCarInfoManage.h"
#include "UserInfoDlg.h"
#include "afxdialogex.h"


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


}


void CUserInfoDlg::SetOperateType(BYTE bType,PUserTableInfo pInfo/*=NULL*/)
{
	m_bOperateType = bType;

	switch(bType)
	{
	case OPERATE_TYPE_ADD:
		{
			SetDlgItemText(IDC_EDIT_userLicNumber,"");
			SetDlgItemText(IDC_EDIT_userName,"");
			SetDlgItemText(IDC_EDIT_userPhone,"");
			SetDlgItemText(IDC_EDIT_userAddress,"");
			SetDlgItemText(IDC_EDIT_userReserve,"");

			m_addMotifyButton.SetWindowText("Ôö¼Ó");
			m_addMotifyButton.ShowWindow(SW_SHOW);
			m_userInfo.Clear();
		}
		break;
	case OPERATE_TYPE_MODIFY:
	case OPERATE_TYPE_SHOW:

		SetDlgItemText(IDC_EDIT_userLicNumber,m_userInfo.csLicenseNumber);
		SetDlgItemText(IDC_EDIT_userName,m_userInfo.csUserName);
		SetDlgItemText(IDC_EDIT_userPhone,m_userInfo.csUserPhone);
		SetDlgItemText(IDC_EDIT_userAddress,m_userInfo.csUserAddress);
		SetDlgItemText(IDC_EDIT_userReserve,m_userInfo.strUserReserve.c_str());

		if(OPERATE_TYPE_MODIFY == m_bOperateType)
		{
			m_addMotifyButton.SetWindowText("ÐÞ¸Ä");
			m_addMotifyButton.ShowWindow(SW_SHOW);
		}
		else
		{
			m_addMotifyButton.ShowWindow(SW_HIDE);
		}
		
		break;
	}
}