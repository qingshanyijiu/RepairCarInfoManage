#pragma once


// CUserMngQueryDlg �Ի���

class CUserMngQueryDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserMngQueryDlg)

public:
	CUserMngQueryDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserMngQueryDlg();

// �Ի�������
	enum { IDD = IDD_USERMNG_QUERY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	CButton m_groupbox;
};
