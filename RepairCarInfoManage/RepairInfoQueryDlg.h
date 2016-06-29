#pragma once


// CRepairInfoQueryDlg dialog

class CRepairInfoQueryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRepairInfoQueryDlg)

public:
	CRepairInfoQueryDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRepairInfoQueryDlg();

// Dialog Data
	enum { IDD = IDD_MaintenanceMng_QUERY_Dlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRclickListRepairlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListRepairlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSmenuRepairdelete();
	afx_msg void OnSmenuRepairdetail();
	afx_msg void OnSmenuRepairmodify();
	afx_msg void OnSmenuRepairqueryuser();
	virtual BOOL OnInitDialog();
};
