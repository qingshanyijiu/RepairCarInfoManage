#pragma once


// CMaintenanceMngDlg 对话框

class CMaintenanceMngDlg : public CDialog
{
	DECLARE_DYNAMIC(CMaintenanceMngDlg)

public:
	CMaintenanceMngDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMaintenanceMngDlg();

// 对话框数据
	enum { IDD = IDD_MaintenanceMng_Dlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
