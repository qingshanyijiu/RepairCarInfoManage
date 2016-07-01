// RepairInfoQueryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RepairCarInfoManage.h"
#include "RepairInfoQueryDlg.h"
#include "afxdialogex.h"
#include "RepairCarInfoManageDlg.h"
#include "RepairInfoDlg.h"
#include "UserMngQueryDlg.h"

extern CRepairCarInfoManageDlg*	g_pMainDlg;

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
	DDX_Control(pDX, IDC_DATETIMEPICKER_Date, m_dateCtrl);
	DDX_Control(pDX, IDC_COMBO_Query, m_queryCombo);
	DDX_Control(pDX, IDC_EDIT_Query, m_queryEdit);
	DDX_Control(pDX, IDC_STATIC_QueryKey, m_queryStatic);
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
	ON_CBN_SELCHANGE(IDC_COMBO_Query, &CRepairInfoQueryDlg::OnSelchangeComboQuery)
END_MESSAGE_MAP()


// CRepairInfoQueryDlg message handlers


void CRepairInfoQueryDlg::OnRclickListRepairlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(m_repairinfolist.GetSelectedCount()>0)
	{
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
	}
	
	*pResult = 0;
}


void CRepairInfoQueryDlg::OnDblclkListRepairlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	CRepairInfoQueryDlg::OnSmenuRepairdetail();

	*pResult = 0;
}


void CRepairInfoQueryDlg::OnSmenuRepairdelete()
{
	// TODO: Add your command handler code here
	int selectIndex = m_repairinfolist.GetSelectionMark();
	if(selectIndex<0)
		return;

	if(IDYES== MessageBox("是否删除当前选中的维修信息?","提示",MB_YESNO))
	{
		int iID = atoi(m_repairinfolist.GetItemText(selectIndex,4));
		if(REPAIRCARINFOSAVEDB_SUCCESS == DeleteRepairInfoByID(iID))
		{
			m_repairinfolist.DeleteItem(selectIndex);
			CRepairCarInfoManageDlg::ShowOperateInfo("维修信息删除成功！");
		}
		else
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("维修信息删除失败！");
		}

	}
}


void CRepairInfoQueryDlg::OnSmenuRepairdetail()
{
	// TODO: Add your command handler code here
	if(g_pMainDlg == NULL || m_repairinfolist.GetSelectedCount()<=0)
		return;
	int selectIndex = m_repairinfolist.GetSelectionMark();
	((CRepairInfoDlg*)(g_pMainDlg->m_pages[IDD_MaintenanceMng_MODIFY_Dlg]))->SetOperateType(OPERATE_TYPE_SHOW,&m_repairInfoVect[selectIndex]);
	g_pMainDlg->RightPageShow(IDD_MaintenanceMng_MODIFY_Dlg);
	CRepairCarInfoManageDlg::ShowOperateInfo("维修信息 - 详细内容！");
}


void CRepairInfoQueryDlg::OnSmenuRepairmodify()
{
	// TODO: Add your command handler code here
	if(g_pMainDlg == NULL || m_repairinfolist.GetSelectedCount()<=0)
		return;
	int selectIndex = m_repairinfolist.GetSelectionMark();
	((CRepairInfoDlg*)(g_pMainDlg->m_pages[IDD_MaintenanceMng_MODIFY_Dlg]))->SetOperateType(OPERATE_TYPE_MODIFY,&m_repairInfoVect[selectIndex]);
	g_pMainDlg->RightPageShow(IDD_MaintenanceMng_MODIFY_Dlg);
	CRepairCarInfoManageDlg::ShowOperateInfo("维修信息 - 修改！");
}


void CRepairInfoQueryDlg::OnSmenuRepairqueryuser()
{
	// TODO: Add your command handler code here
	if(g_pMainDlg == NULL || m_repairinfolist.GetSelectedCount()<=0)
		return;

	int selectIndex = m_repairinfolist.GetSelectionMark();
	((CUserMngQueryDlg*)(g_pMainDlg->m_pages[IDD_USERMNG_QUERY_DLG]))->QueryUserInfoByLicNumber(m_repairInfoVect[selectIndex].csLicenseNumber);
	g_pMainDlg->RightPageShow(IDD_USERMNG_QUERY_DLG);
	CRepairCarInfoManageDlg::ShowOperateInfo("车主信息 - 详细内容！");
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
	m_repairinfolist.InsertColumn( 1, "修车日期", LVCFMT_LEFT, 80 );
	m_repairinfolist.InsertColumn( 2, "下次路程", LVCFMT_LEFT, 80 );
	m_repairinfolist.InsertColumn( 3, "修车内容", LVCFMT_LEFT, 150 );
	m_repairinfolist.InsertColumn( 4, "修车项目", LVCFMT_LEFT, 150 );
	m_repairinfolist.InsertColumn( 5, "备注", LVCFMT_LEFT, 150 );
	m_repairinfolist.InsertColumn( 6, "ID", LVCFMT_LEFT, 0 );

	m_queryCombo.InsertString(0,"查询所有");
	m_queryCombo.InsertString(1,"按车牌号");
	m_queryCombo.InsertString(2,"按修车日期");
	m_queryCombo.InsertString(3,"按下次路程");
	m_queryCombo.InsertString(4,"修车内容");
	m_queryCombo.InsertString(5,"修车项目");
	m_queryCombo.InsertString(6,"修车项目");

	m_queryCombo.SetCurSel(0);
	m_queryEdit.ShowWindow(SW_HIDE);
	m_dateCtrl.ShowWindow(SW_HIDE);
	m_queryStatic.ShowWindow(SW_HIDE);
	m_queryEdit.SetParent(this);
	m_dateCtrl.SetParent(this);

	CRect combRect,tempRect;
	m_queryCombo.GetWindowRect(&combRect);
	combRect.top -= 30;
	combRect.bottom -=30;

	m_queryEdit.GetWindowRect(&tempRect);
	tempRect.top = combRect.top;
	tempRect.bottom = combRect.bottom;
	m_queryEdit.MoveWindow(&tempRect);

	m_dateCtrl.GetWindowRect(&tempRect);
	tempRect.top = combRect.top;
	tempRect.bottom = combRect.bottom;
	m_dateCtrl.MoveWindow(&tempRect);

	m_dateCtrl.SetTime(&CTime::GetCurrentTime());
	CTimeSpan timespanOneMonth(180,0,0,0); //这里设置为当前日期推后180天 3

	m_curpage = 0;
	m_repairInfoVect.reserve(MAX_QUERY_COUNT);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CRepairInfoQueryDlg::OnBnClickedBtnMtQrepairinfo()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	m_curpage = 0;
	m_repairInfoVect.clear();
	m_queryInfo.Clear();

	switch(m_queryCombo.GetCurSel())
	{
	case 1:
		{
			CString	strTemp;
			GetDlgItemText(IDC_EDIT_Query,strTemp);
			strncpy(m_queryInfo.csLicenseNumber,strTemp.operator LPCSTR(),32);
		}
		break;
	case 2:
		{
			CTime  tempTime;
			m_dateCtrl.GetTime(tempTime);
			strncpy(m_queryInfo.csRepairDate,tempTime.Format("%Y-%m-%d").operator LPCSTR(),32);
		}
		break;
	case 3:
		{
			CTime  tempTime;
			m_dateCtrl.GetTime(tempTime);
			strncpy(m_queryInfo.csRepairNextDate,tempTime.Format("%Y-%m-%d").operator LPCSTR(),32);
		}
		break;
	case 4:
		{
			CString	strTemp;
			GetDlgItemText(IDC_EDIT_Query,strTemp);
			m_queryInfo.strRepairNotes = strTemp.operator LPCSTR();
		}
		break;
	case 5:
		{
			CString	strTemp;
			GetDlgItemText(IDC_EDIT_Query,strTemp);
			m_queryInfo.strRepairItems = strTemp.operator LPCSTR();
		}
		break;
	case 6:
		{
			CString	strTemp;
			GetDlgItemText(IDC_EDIT_Query,strTemp);
			m_queryInfo.strRepairReserve = strTemp.operator LPCSTR();
		}
		break;
	}

	if(REPAIRCARINFOSAVEDB_SUCCESS != GetRepairInfo(&m_queryInfo,m_curpage,MAX_QUERY_COUNT,m_repairInfoVect,true))
	{
		CRepairCarInfoManageDlg::ShowOperateInfo("维修信息查询失败！");
		return;
	}

	UpdateDataInfo();
	if(m_repairInfoVect.size()>0)
		CRepairCarInfoManageDlg::ShowOperateInfo("维修信息查询成功！");
	else
		CRepairCarInfoManageDlg::ShowOperateInfo("没有查询到对应的维修信息！");
}

void CRepairInfoQueryDlg::QueryRepairInfoByLicNumber(const char* lpLicNumber)
{
	SetDlgItemText(IDC_EDIT_QrepairLicNumber,lpLicNumber);
	//SetDlgItemText(IDC_EDIT_QrepairDate,"");

	OnBnClickedBtnMtQrepairinfo();
}


void CRepairInfoQueryDlg::OnBnClickedButtonQuserbefore()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if(m_curpage<=0)
	{
		CRepairCarInfoManageDlg::ShowOperateInfo("没有上一页了，查询失败！");
		return;
	}
	
	--m_curpage;
	m_repairInfoVect.clear();
	
	if(REPAIRCARINFOSAVEDB_SUCCESS != GetRepairInfo(&m_queryInfo,m_curpage,MAX_QUERY_COUNT,m_repairInfoVect,true))
	{
		CRepairCarInfoManageDlg::ShowOperateInfo("查询上一页失败！");
		return;
	}
	if(m_repairInfoVect.size()<=0)
	{
		++m_curpage;
		UpdateDataInfo();
		CRepairCarInfoManageDlg::ShowOperateInfo("没有上一页了，查询失败！");
	}
	else
	{
		UpdateDataInfo();
		CRepairCarInfoManageDlg::ShowOperateInfo("查询上一页成功！");
	}
}


void CRepairInfoQueryDlg::OnBnClickedButtonQusernext()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	if(m_repairInfoVect.size()<MAX_QUERY_COUNT)
	{
		CRepairCarInfoManageDlg::ShowOperateInfo("没有下一页了，查询失败！");
		return;
	}

	++m_curpage;
	m_repairInfoVect.clear();

	if(REPAIRCARINFOSAVEDB_SUCCESS != GetRepairInfo(&m_queryInfo,m_curpage,MAX_QUERY_COUNT,m_repairInfoVect,true))
	{
		CRepairCarInfoManageDlg::ShowOperateInfo("查询下一页失败！");
		--m_curpage;
		return;
	}

	if(m_repairInfoVect.size()<=0)
	{
		--m_curpage;
		UpdateDataInfo();
		CRepairCarInfoManageDlg::ShowOperateInfo("没有下一页了，查询失败！");
	}
	else
	{
		UpdateDataInfo();
		CRepairCarInfoManageDlg::ShowOperateInfo("查询下一页成功！");
	}
}


void	CRepairInfoQueryDlg::UpdateDataInfo()
{
	m_repairinfolist.SetRedraw(FALSE);
	//更新内容
	m_repairinfolist.DeleteAllItems();

	int nRow;
	char idstr[10];
	for(int i = 0 ; i < m_repairInfoVect.size() ; ++i) 
	{ 
		nRow = m_repairinfolist.InsertItem(i,m_repairInfoVect[i].csLicenseNumber);
		m_repairinfolist.SetItemText(nRow,1,m_repairInfoVect[i].csRepairDate);
		m_repairinfolist.SetItemText(nRow,2,m_repairInfoVect[i].csRepairNextDate);
		m_repairinfolist.SetItemText(nRow,3,m_repairInfoVect[i].strRepairNotes.c_str());
		m_repairinfolist.SetItemText(nRow,4,m_repairInfoVect[i].strRepairItems.c_str());
		m_repairinfolist.SetItemText(nRow,5,m_repairInfoVect[i].strRepairReserve.c_str());
		sprintf_s(idstr,"%d",m_repairInfoVect[i].iID);
		m_repairinfolist.SetItemText(nRow,6,idstr);
	} 

	m_repairinfolist.SetRedraw(TRUE);
	m_repairinfolist.Invalidate();
	m_repairinfolist.UpdateWindow();
}

BOOL CRepairInfoQueryDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	// 把Esc和Enter按键事件消息过滤掉，否则该消息会导致对应应用程序调用OnOK（）方法，结束应用程序
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE: //Esc按键事件
			return true;
		case VK_RETURN: //Enter按键事件
			OnBnClickedBtnMtQrepairinfo();
			return true;
		default:
			;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CRepairInfoQueryDlg::OnSelchangeComboQuery()
{
	// TODO: Add your control notification handler code here
	m_queryEdit.ShowWindow(SW_HIDE);
	m_dateCtrl.ShowWindow(SW_HIDE);
	m_queryStatic.ShowWindow(SW_HIDE);

	switch(m_queryCombo.GetCurSel())
	{
	case 0:
		break;
	case 2:case 3:
		m_dateCtrl.ShowWindow(SW_SHOW);
		m_queryStatic.ShowWindow(SW_SHOW);
		break;
	default:
		m_queryEdit.ShowWindow(SW_SHOW);
		m_queryStatic.ShowWindow(SW_SHOW);
		break;
	}
}
