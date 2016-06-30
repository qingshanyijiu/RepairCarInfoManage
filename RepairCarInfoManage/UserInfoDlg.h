#pragma once
#include "afxwin.h"


// CUserInfoDlg dialog

class CUserInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserInfoDlg)

public:
	CUserInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserInfoDlg();

// Dialog Data
	enum { IDD = IDD_USERMNG_MODIFY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_addMotifyButton;
	afx_msg void OnBnClickedBtnUserAdd();


public:
	UserTableInfo	m_userInfo;
	BYTE			m_bOperateType;

public:
	void	SetOperateType(BYTE bType,PUserTableInfo pInfo=NULL);

public:
	CEdit m_userAddreEdit;
	CEdit m_userLicNumberEdit;
	CEdit m_userNameEdit;
	CEdit m_userPhoneEdit;
	CEdit m_userReserveEdit;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreInitDialog();
};
