#pragma once


// CRepairInfoDlg dialog

class CRepairInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRepairInfoDlg)
public:
	RepairTableInfo			m_repairInfo;
	BYTE					m_bOperateType;
	void	SetOperateType(BYTE bType,PRepairTableInfo pInfo=NULL);
public:
	CRepairInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRepairInfoDlg();

// Dialog Data
	enum { IDD = IDD_MaintenanceMng_MODIFY_Dlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnRepairadd();
	CEdit m_RepairLicNumber;
	CEdit m_RepairNotes;
	CEdit m_RepairReserve;
	CButton m_AddModifyButton;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CDateTimeCtrl m_dateCtrl;
	CDateTimeCtrl m_nextDateCtrl;
};
