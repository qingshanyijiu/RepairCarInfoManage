
// RepairCarInfoManageDlg.h : ͷ�ļ�
//

#pragma once
#include <vector>
#include <map>
class CButtonExd;

// CRepairCarInfoManageDlg �Ի���
class CRepairCarInfoManageDlg : public CDialogEx
{
// ����
public:
	CRepairCarInfoManageDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_REPAIRCARINFOMANAGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
private:
	typedef std::vector<CDialog *> PageArray;
	typedef std::map<long,std::vector<long> > BTNREL;
	PageArray m_pages;
	BOOL ShowParamDlg(CWnd* pWnd, BOOL bShow);
	CWnd* m_pCurrentWnd;
	BTNREL m_btnRel;
	CButtonExd* m_root;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnUsermng();
	afx_msg void OnBnClickedBtnMtinfomng();
};
