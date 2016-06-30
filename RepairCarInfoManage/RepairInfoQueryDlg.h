#pragma once
#include <vector>
using namespace std;


// CRepairInfoQueryDlg dialog
class CRepairCarInfoManageDlg;
class CRepairInfoQueryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRepairInfoQueryDlg)

public:
	CRepairInfoQueryDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRepairInfoQueryDlg();
	CRepairCarInfoManageDlg* m_parent;
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
	CListCtrl m_repairinfolist;
	afx_msg void OnBnClickedBtnMtQrepairinfo();
	afx_msg void OnBnClickedButtonQuserbefore();
	afx_msg void OnBnClickedButtonQusernext();
private:
	int							m_curpage;
	vector<RepairTableInfo>		m_repairInfoVect;

public:
	void	UpdateDataInfo();
	
};
