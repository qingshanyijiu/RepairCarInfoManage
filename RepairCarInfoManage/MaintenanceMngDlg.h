#pragma once


// CMaintenanceMngDlg �Ի���

class CMaintenanceMngDlg : public CDialog
{
	DECLARE_DYNAMIC(CMaintenanceMngDlg)

public:
	CMaintenanceMngDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMaintenanceMngDlg();

// �Ի�������
	enum { IDD = IDD_MaintenanceMng_Dlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
