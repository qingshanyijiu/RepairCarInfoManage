#pragma once


// CUserMngDlg �Ի���

class CUserMngDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserMngDlg)

public:
	CUserMngDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserMngDlg();

// �Ի�������
	enum { IDD = IDD_USERMNG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
