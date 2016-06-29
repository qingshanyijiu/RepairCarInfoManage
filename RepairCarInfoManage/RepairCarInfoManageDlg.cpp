
// RepairCarInfoManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RepairCarInfoManage.h"
#include "RepairCarInfoManageDlg.h"
#include "afxdialogex.h"
#include "UserMngQueryDlg.h"
#include "MaintenanceMngDlg.h"
#include "ButtonExd.h"

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
	m_root = new CButtonExd();
	m_root->InitBtnMap();
}

void CRepairCarInfoManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRepairCarInfoManageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
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

	//用户管理 
	//查询
	pWnd = new CDialog();
	pWnd->Create(IDD_USERMNG_QUERY_DLG,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_USERMNG_QUERY_DLG] = pWnd;
	//增加/修改
	pWnd = new CUserMngQueryDlg();
	pWnd->Create(IDD_USERMNG_MODIFY_DLG,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_USERMNG_MODIFY_DLG] = pWnd;

	//维护信息
	//查询
	pWnd = new CDialog();
	pWnd->Create(IDD_MaintenanceMng_QUERY_Dlg,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_MaintenanceMng_QUERY_Dlg] = pWnd;
	//增加/修改
	pWnd = new CDialog();
	pWnd->Create(IDD_MaintenanceMng_MODIFY_Dlg,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_MaintenanceMng_MODIFY_Dlg] = pWnd;

	//系统设置
	//基本配置
	pWnd = new CDialog();
	pWnd->Create(IDD_SYSSET_BASIC_DLG,this);
	ShowParamDlg(pWnd,FALSE);
	m_pages[IDD_SYSSET_BASIC_DLG] = pWnd;
	
	int leftpad =0,toppad =0;
	CButtonExd *pCurrent=m_root,*pChild =NULL;
	CRect PRect,ChildRect;
	GetDlgItem(IDC_BTN_USERMNG)->GetWindowRect(&PRect);
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BTN_USERMNG),_T("用户信息管理"),IDC_BTN_USERMNG,0,2);	
	pCurrent->AddChild(pChild);
	pChild->SetBeforeLBClickDealFunc(std::tr1::bind(&CRepairCarInfoManageDlg::TestBofore, this));
	pChild->SetAfterLBClickDealFunc(std::tr1::bind(&CRepairCarInfoManageDlg::TestAfter, this));
	pChild->SetAbsolutePos(true);

	pCurrent = pChild;
	GetDlgItem(IDC_BTN_USERMODIFY)->GetWindowRect(&ChildRect);
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BTN_USERMODIFY),_T("增加/修改"),IDC_BTN_USERMODIFY,PRect.Width()-ChildRect.Width(),2);
	pCurrent->AddChild(pChild);

	GetDlgItem(IDC_BTN_USERQUERY)->GetWindowRect(&ChildRect);
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BTN_USERQUERY),_T("查询"),IDC_BTN_USERQUERY,0,2);
	pCurrent->AddChild(pChild);

	pCurrent=m_root;
	GetDlgItem(IDC_BTN_MTINFOMNG)->GetWindowRect(&PRect);
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BTN_MTINFOMNG),_T("维护信息管理"),IDC_BTN_MTINFOMNG,0,2);	
	pCurrent->AddChild(pChild);

	pCurrent = pChild;
	GetDlgItem(IDC_BTN_MTMODIFY)->GetWindowRect(&ChildRect);
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BTN_MTMODIFY),_T("增加/修改"),IDC_BTN_MTMODIFY,PRect.Width()-ChildRect.Width(),2);
	pCurrent->AddChild(pChild);

	GetDlgItem(IDC_BTN_MTQUERY)->GetWindowRect(&ChildRect);
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BTN_MTQUERY),_T("查询"),IDC_BTN_MTQUERY,0,2);
	pCurrent->AddChild(pChild);

	pCurrent=m_root;
	GetDlgItem(IDC_BUTTON_SystemSet)->GetWindowRect(&PRect);
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BUTTON_SystemSet),_T("系统设置"),0,2);	
	pCurrent->AddChild(pChild);

	pCurrent = pChild;
	GetDlgItem(IDC_BUTTON_BasicSet)->GetWindowRect(&ChildRect);
	pChild= new CButtonExd(this,(CButton*)GetDlgItem(IDC_BUTTON_BasicSet),_T("基本设置"),IDC_BUTTON_BasicSet,PRect.Width()-ChildRect.Width(),2);
	pCurrent->AddChild(pChild);

	

	m_root->Show();
	m_root->Expand();
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

void CRepairCarInfoManageDlg::TestBofore()
{
	MessageBox(_T("before"));
}
void CRepairCarInfoManageDlg::TestAfter()
{
	MessageBox(_T("after"));
}


void CRepairCarInfoManageDlg::Expand(int index)
{
	if(m_root == NULL)
		return;
	int BigMenus = m_root->m_Childs.size();
	if(index >BigMenus-1)
		return;
	if( !m_root->m_Childs[index]->IsShow())
		return;
	if(m_root->m_Childs[index]->IsExpand())
		return;
	m_root->m_Childs[index]->Expand();
	for (int i=BigMenus-1;i>=0;--i)
	{
		if(i!=index)
		{
			m_root->m_Childs[i]->Folded();
		}
	}
	if(index<BigMenus-1)
	{
		CRect rc = m_root->m_Childs[BigMenus-1]->GetRect();
		CRect DlgRc;
		GetClientRect(&DlgRc);
		int toppad = DlgRc.bottom-rc.bottom;
		m_root->m_Childs[index]->Revise(0,toppad);
	}
}

void CRepairCarInfoManageDlg::OnBnClickedBtnUsermng()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	/*if (m_pCurrentWnd != NULL)
	{
		m_pCurrentWnd->ShowWindow(SW_HIDE);
	}

	m_pCurrentWnd = m_pages.at(0);
	m_pCurrentWnd->ShowWindow(SW_SHOW);*/
	return;
	if(m_root->m_Childs[0]->IsExpand())
		m_root->m_Childs[0]->Folded();
	else
		Expand(0);
}


void CRepairCarInfoManageDlg::OnBnClickedBtnMtinfomng()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if(m_root->m_Childs[1]->IsExpand())
		m_root->m_Childs[1]->Folded();
	else
		Expand(1);
}


void CRepairCarInfoManageDlg::OnBnClickedButtonSystemset()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if(m_root->m_Childs[2]->IsExpand())
		m_root->m_Childs[2]->Folded();
	else
		Expand(2);
}

void CRepairCarInfoManageDlg::RightPageShow(long DLGID)
{
	if(m_pages[DLGID] == NULL)
		return;
	if (m_pCurrentWnd != NULL)
	{
		m_pCurrentWnd->ShowWindow(SW_HIDE);
	}

	m_pCurrentWnd = m_pages[DLGID];
	m_pCurrentWnd->ShowWindow(SW_SHOW);
}

void CRepairCarInfoManageDlg::OnBnClickedBtnUserquery()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	RightPageShow(IDD_USERMNG_QUERY_DLG);
}


void CRepairCarInfoManageDlg::OnBnClickedBtnUsermodify()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	RightPageShow(IDD_USERMNG_MODIFY_DLG);
}


void CRepairCarInfoManageDlg::OnBnClickedBtnMtquery()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	RightPageShow(IDD_MaintenanceMng_QUERY_Dlg);
}


void CRepairCarInfoManageDlg::OnBnClickedBtnMtmodify()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	RightPageShow(IDD_MaintenanceMng_MODIFY_Dlg);
}


void CRepairCarInfoManageDlg::OnBnClickedButtonBasicset()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	RightPageShow(IDD_SYSSET_BASIC_DLG);
}


BOOL CRepairCarInfoManageDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà
	if( (LOWORD(wParam) >= 1000 ) && (LOWORD(wParam) <= 1100 )) 
	{ 
		if(CButtonExd::OnCommond(m_root,wParam,lParam))
			return true; 
	} 

	return CDialogEx::OnCommand(wParam, lParam);
}


BOOL CRepairCarInfoManageDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	return CDialogEx::PreTranslateMessage(pMsg);
}
