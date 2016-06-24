
// RepairCarInfoManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RepairCarInfoManage.h"
#include "RepairCarInfoManageDlg.h"
#include "afxdialogex.h"
#include "UserMngDlg.h"
#include "MaintenanceMngDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  BTN_ROOT 0
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRepairCarInfoManageDlg 对话框




CRepairCarInfoManageDlg::CRepairCarInfoManageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRepairCarInfoManageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pCurrentWnd = NULL;
}

void CRepairCarInfoManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRepairCarInfoManageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_USERMNG, &CRepairCarInfoManageDlg::OnBnClickedBtnUsermng)
	ON_BN_CLICKED(IDC_BTN_MTINFOMNG, &CRepairCarInfoManageDlg::OnBnClickedBtnMtinfomng)
END_MESSAGE_MAP()


// CRepairCarInfoManageDlg 消息处理程序

BOOL CRepairCarInfoManageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	/*// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	*/
	// TODO: 在此添加额外的初始化代码
	CDialog* pWnd = nullptr;

	//用户管理page
	pWnd = new CUserMngDlg();
	pWnd->Create(CUserMngDlg::IDD,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages.push_back(pWnd);

	//维护管理page
	pWnd = new CMaintenanceMngDlg();
	pWnd->Create(CMaintenanceMngDlg::IDD,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages.push_back(pWnd);

	m_btnRel[BTN_ROOT].push_back(IDC_BTN_USERMNG);
	m_btnRel[BTN_ROOT].push_back(IDC_BTN_MTINFOMNG);
	m_btnRel[IDC_BTN_USERMNG].push_back(IDC_BTN_USERQUERY);
	m_btnRel[IDC_BTN_USERMNG].push_back(IDC_BTN_USERADD);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRepairCarInfoManageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRepairCarInfoManageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRepairCarInfoManageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CRepairCarInfoManageDlg::ShowParamDlg(CWnd* pWnd, BOOL bShow)
{
	if (pWnd == NULL)
	{
		return FALSE;
	}

	CRect rc;
	GetDlgItem(IDC_PlaceHolder)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	pWnd->MoveWindow(&rc);
	return pWnd->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
}


void CRepairCarInfoManageDlg::OnBnClickedBtnUsermng()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if (m_pCurrentWnd != NULL)
	{
		m_pCurrentWnd->ShowWindow(SW_HIDE);
	}

	m_pCurrentWnd = m_pages.at(0);
	m_pCurrentWnd->ShowWindow(SW_SHOW);
}


void CRepairCarInfoManageDlg::OnBnClickedBtnMtinfomng()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if (m_pCurrentWnd != NULL)
	{
		m_pCurrentWnd->ShowWindow(SW_HIDE);
	}

	m_pCurrentWnd = m_pages.at(1);
	m_pCurrentWnd->ShowWindow(SW_SHOW);
}
