#pragma once


// CUserMngDlg 对话框

class CUserMngDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserMngDlg)

public:
	CUserMngDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserMngDlg();

// 对话框数据
	enum { IDD = IDD_USERMNG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
