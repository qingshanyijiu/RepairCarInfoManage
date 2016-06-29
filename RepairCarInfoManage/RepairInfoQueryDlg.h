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
};
