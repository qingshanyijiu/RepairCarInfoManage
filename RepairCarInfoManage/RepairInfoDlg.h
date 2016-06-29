#pragma once


// CRepairInfoDlg dialog

class CRepairInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRepairInfoDlg)

public:
	CRepairInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRepairInfoDlg();

// Dialog Data
	enum { IDD = IDD_MaintenanceMng_MODIFY_Dlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
