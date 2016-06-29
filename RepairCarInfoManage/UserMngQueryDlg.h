#pragma once


// CUserMngQueryDlg 对话框

class CUserMngQueryDlg : public CDialogEx
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
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnUserUserquery();
	afx_msg void OnBnClickedButtonQuserbefore();
	afx_msg void OnBnClickedButtonQusernext();
	CButton m_QUserBeforeButton;
	CButton m_QUserNextButton;
	CListCtrl m_userList;
//	afx_msg void OnLvnItemchangedListUserlist(NMHDR *pNMHDR, LRESULT *pResult);

public:

	afx_msg void OnRclickListUserlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListUserlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSmenuUserdelete();
	afx_msg void OnSmenuUserdetail();
	afx_msg void OnSmenuUsermodify();
	afx_msg void OnSmenuUserqueryrepair();
};
