
// RepairCarInfoManageDlg.h : 头文件
//

#pragma once
#include <vector>
#include <map>
class CButtonExd;

// CRepairCarInfoManageDlg 对话框
class CRepairCarInfoManageDlg : public CDialogEx
{
// 构造
public:
	CRepairCarInfoManageDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_REPAIRCARINFOMANAGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
private:
	typedef std::map<long,CDialog *> PageMap;
	PageMap m_pages;
	BOOL ShowParamDlg(CWnd* pWnd, BOOL bShow);
	CWnd* m_pCurrentWnd;
	CButtonExd* m_root;
// 实现
protected:
	HICON m_hIcon;
	void Expand(int index);
	void RightPageShow(long DLGID);
	void AfterButtonClick(void*);
	void TestBofore(void* );
	void TestAfter(void*);
	// 生成的消息映射函数
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
