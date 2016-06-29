// RepairInfoQueryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RepairCarInfoManage.h"
#include "RepairInfoQueryDlg.h"
#include "afxdialogex.h"


// CRepairInfoQueryDlg dialog

IMPLEMENT_DYNAMIC(CRepairInfoQueryDlg, CDialogEx)

CRepairInfoQueryDlg::CRepairInfoQueryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRepairInfoQueryDlg::IDD, pParent)
{
	m_curpage = 0;
}

CRepairInfoQueryDlg::~CRepairInfoQueryDlg()
{
}

void CRepairInfoQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RepairList, m_repairinfolist);
}


BEGIN_MESSAGE_MAP(CRepairInfoQueryDlg, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_RepairList, &CRepairInfoQueryDlg::OnRclickListRepairlist)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RepairList, &CRepairInfoQueryDlg::OnDblclkListRepairlist)
	ON_COMMAND(ID_SMENU_RepairDelete, &CRepairInfoQueryDlg::OnSmenuRepairdelete)
	ON_COMMAND(ID_SMENU_RepairDetail, &CRepairInfoQueryDlg::OnSmenuRepairdetail)
	ON_COMMAND(ID_SMENU_RepairModify, &CRepairInfoQueryDlg::OnSmenuRepairmodify)
	ON_COMMAND(ID_SMENU_RepairQueryUser, &CRepairInfoQueryDlg::OnSmenuRepairqueryuser)
	ON_BN_CLICKED(IDC_BTN_MT_QRepairInfo, &CRepairInfoQueryDlg::OnBnClickedBtnMtQrepairinfo)
	ON_BN_CLICKED(IDC_BUTTON_QUserBefore, &CRepairInfoQueryDlg::OnBnClickedButtonQuserbefore)
	ON_BN_CLICKED(IDC_BUTTON_QUserNext, &CRepairInfoQueryDlg::OnBnClickedButtonQusernext)
END_MESSAGE_MAP()


// CRepairInfoQueryDlg message handlers


void CRepairInfoQueryDlg::OnRclickListRepairlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//if(pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU_RepairMenu ) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
	}
	*pResult = 0;
}


void CRepairInfoQueryDlg::OnDblclkListRepairlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	

	*pResult = 0;
}


void CRepairInfoQueryDlg::OnSmenuRepairdelete()
{
	// TODO: Add your command handler code here
}


void CRepairInfoQueryDlg::OnSmenuRepairdetail()
{
	// TODO: Add your command handler code here
}


void CRepairInfoQueryDlg::OnSmenuRepairmodify()
{
	// TODO: Add your command handler code here
}


void CRepairInfoQueryDlg::OnSmenuRepairqueryuser()
{
	// TODO: Add your command handler code here
}


BOOL CRepairInfoQueryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	LONG lStyle;
	lStyle = GetWindowLong(m_repairinfolist.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_repairinfolist.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD dwStyle = m_repairinfolist.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_repairinfolist.SetExtendedStyle(dwStyle); //设置扩展风格

	m_repairinfolist.InsertColumn( 0, "车牌号", LVCFMT_LEFT, 80 );
	m_repairinfolist.InsertColumn( 1, "日期", LVCFMT_LEFT, 100 );
	m_repairinfolist.InsertColumn( 2, "修车信息", LVCFMT_LEFT, 300 );
	m_repairinfolist.InsertColumn( 3, "备注", LVCFMT_LEFT, 300 );
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CRepairInfoQueryDlg::OnBnClickedBtnMtQrepairinfo()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CString	strTemp;
	RepairTableInfo rinfo;
	GetDlgItemText(IDC_EDIT_QrepairLicNumber,strTemp);
	strncpy(rinfo.csLicenseNumber,strTemp.operator LPCSTR(),16);
	GetDlgItemText(IDC_EDIT_QrepairDate,strTemp);
	strncpy(rinfo.csRepairDate,strTemp.operator LPCSTR(),16);
	m_curpage = 0;
	std::vector<RepairTableInfo> repairInfoList;
	GetRepairInfo(&rinfo,m_curpage,10,repairInfoList,true);
	int count = repairInfoList.size();
	m_repairinfolist.DeleteAllItems();
	int nRow =0;
	for (int i=0;i<count;++i)
	{
		nRow = m_repairinfolist.InsertItem(i,repairInfoList[i].csLicenseNumber);
		m_repairinfolist.SetItemText(nRow,1,repairInfoList[i].csRepairDate);
		m_repairinfolist.SetItemText(nRow,2,repairInfoList[i].strRepairNotes.c_str());
		m_repairinfolist.SetItemText(nRow,3,repairInfoList[i].strRepairReserve.c_str());
	}
}


void CRepairInfoQueryDlg::OnBnClickedButtonQuserbefore()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
}


void CRepairInfoQueryDlg::OnBnClickedButtonQusernext()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
}
