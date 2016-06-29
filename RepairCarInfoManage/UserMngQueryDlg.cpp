// UserMngQueryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RepairCarInfoManage.h"
#include "UserMngQueryDlg.h"
#include "afxdialogex.h"


// CUserMngQueryDlg 对话框

IMPLEMENT_DYNAMIC(CUserMngQueryDlg, CDialogEx)

CUserMngQueryDlg::CUserMngQueryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserMngQueryDlg::IDD, pParent)
{

}

CUserMngQueryDlg::~CUserMngQueryDlg()
{
}

void CUserMngQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_GROUPBOX_USERQUEY, m_groupbox);
	DDX_Control(pDX, IDC_BUTTON_QUserBefore, m_QUserBeforeButton);
	DDX_Control(pDX, IDC_BUTTON_QUserNext, m_QUserNextButton);
	DDX_Control(pDX, IDC_LIST_UserList, m_userList);
}


BEGIN_MESSAGE_MAP(CUserMngQueryDlg, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_USER_UserQuery, &CUserMngQueryDlg::OnBnClickedBtnUserUserquery)
	ON_BN_CLICKED(IDC_BUTTON_QUserBefore, &CUserMngQueryDlg::OnBnClickedButtonQuserbefore)
	ON_BN_CLICKED(IDC_BUTTON_QUserNext, &CUserMngQueryDlg::OnBnClickedButtonQusernext)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_UserList, &CUserMngQueryDlg::OnLvnItemchangedListUserlist)
ON_NOTIFY(NM_RCLICK, IDC_LIST_UserList, &CUserMngQueryDlg::OnRclickListUserlist)
ON_NOTIFY(NM_DBLCLK, IDC_LIST_UserList, &CUserMngQueryDlg::OnDblclkListUserlist)
ON_COMMAND(ID_SMENU_UserDelete, &CUserMngQueryDlg::OnSmenuUserdelete)
ON_COMMAND(ID_SMENU_UserDetail, &CUserMngQueryDlg::OnSmenuUserdetail)
ON_COMMAND(ID_SMENU_UserModify, &CUserMngQueryDlg::OnSmenuUsermodify)
ON_COMMAND(ID_SMENU_UserQueryRepair, &CUserMngQueryDlg::OnSmenuUserqueryrepair)
END_MESSAGE_MAP()


// CUserMngQueryDlg 消息处理程序


void CUserMngQueryDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
}


BOOL CUserMngQueryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	LONG lStyle;
	lStyle = GetWindowLong(m_userList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_userList.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD dwStyle = m_userList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_userList.SetExtendedStyle(dwStyle); //设置扩展风格

	m_userList.InsertColumn( 0, "车牌号", LVCFMT_LEFT, 80 );
	m_userList.InsertColumn( 1, "车主名", LVCFMT_LEFT, 60 );
	m_userList.InsertColumn( 2, "电话", LVCFMT_LEFT, 80 );
	m_userList.InsertColumn( 3, "住址", LVCFMT_LEFT, 150 );
	m_userList.InsertColumn( 4, "备注", LVCFMT_LEFT, 300 );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CUserMngQueryDlg::OnBnClickedBtnUserUserquery()
{
	// TODO: Add your control notification handler code here
}


void CUserMngQueryDlg::OnBnClickedButtonQuserbefore()
{
	// TODO: Add your control notification handler code here
}


void CUserMngQueryDlg::OnBnClickedButtonQusernext()
{
	// TODO: Add your control notification handler code here
}


//void CUserMngQueryDlg::OnLvnItemchangedListUserlist(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	*pResult = 0;
//}


void CUserMngQueryDlg::OnRclickListUserlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//if(pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU_UserMenu ) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
	}

	*pResult = 0;
}


void CUserMngQueryDlg::OnDblclkListUserlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CUserMngQueryDlg::OnSmenuUserdelete()
{
	// TODO: Add your command handler code here
	AfxMessageBox("Dele");
}


void CUserMngQueryDlg::OnSmenuUserdetail()
{
	// TODO: Add your command handler code here
}


void CUserMngQueryDlg::OnSmenuUsermodify()
{
	// TODO: Add your command handler code here
}


void CUserMngQueryDlg::OnSmenuUserqueryrepair()
{
	// TODO: Add your command handler code here
}
