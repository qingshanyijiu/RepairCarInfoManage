
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
	typedef std::map<long,CDialog *> PageMap;
	PageMap m_pages;
	BOOL ShowParamDlg(CWnd* pWnd, BOOL bShow);
	CWnd* m_pCurrentWnd;
	CButtonExd* m_root;
// ʵ��
protected:
	HICON m_hIcon;
	void Expand(int index);
	void RightPageShow(long DLGID);
	void AfterButtonClick(void*);
	void TestBofore(void* );
	void TestAfter(void*);
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnUsermng();
	afx_msg void OnBnClickedBtnMtinfomng();
	afx_msg void OnBnClickedButtonSystemset();
	afx_msg void OnBnClickedBtnUserquery();
	afx_msg void OnBnClickedBtnUsermodify();
	afx_msg void OnBnClickedBtnMtquery();
	afx_msg void OnBnClickedBtnMtmodify();
	afx_msg void OnBnClickedButtonBasicset();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
