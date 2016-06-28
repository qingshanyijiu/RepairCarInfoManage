#pragma once


// CUserMngQueryDlg 对话框

class CUserMngQueryDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserMngQueryDlg)

public:
	CUserMngQueryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserMngQueryDlg();

// 对话框数据
	enum { IDD = IDD_USERMNG_QUERY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	CButton m_groupbox;
};
