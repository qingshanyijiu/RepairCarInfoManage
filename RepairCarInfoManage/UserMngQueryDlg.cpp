// UserMngQueryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RepairCarInfoManage.h"
#include "UserMngQueryDlg.h"
#include "afxdialogex.h"
#include "RepairCarInfoManageDlg.h"
#include "UserInfoDlg.h"
#include "RepairInfoQueryDlg.h"

extern CRepairCarInfoManageDlg*	g_pMainDlg;

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

	m_curPageIndex = 0;
	m_userInfoVect.reserve(MAX_QUERY_COUNT);
	m_pQueryFunc = GetUserInfoByLicNumber;
	m_strQueryKey.clear();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CUserMngQueryDlg::OnBnClickedBtnUserUserquery()
{
	// TODO: Add your control notification handler code here
	CString	strTemp;

	strTemp.Empty();
	m_curPageIndex = 0;
	m_userInfoVect.clear();

	GetDlgItemText(IDC_EDIT_QuserLicNumber,strTemp);
	if (!strTemp.IsEmpty())
	{
		m_strQueryKey = strTemp.operator LPCSTR();
		m_pQueryFunc = GetUserInfoByLicNumber;

		if (REPAIRCARINFOSAVEDB_SUCCESS == m_pQueryFunc(m_strQueryKey.c_str(),
			m_curPageIndex,
			MAX_QUERY_COUNT,
			m_userInfoVect,
			true))
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("按照车牌号查询成功！");
			UpdateDataInfo();
		}
		else
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("按照车牌号查询失败！");
		}

		return;
	}

	GetDlgItemText(IDC_EDIT_QuserName,strTemp);
	if (!strTemp.IsEmpty())
	{
		m_strQueryKey = strTemp.operator LPCSTR();
		m_pQueryFunc = GetUserInfoByName;

		if (REPAIRCARINFOSAVEDB_SUCCESS == m_pQueryFunc(m_strQueryKey.c_str(),
			m_curPageIndex,
			MAX_QUERY_COUNT,
			m_userInfoVect,
			true))
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("按照车主名查询成功！");
			UpdateDataInfo();
		}
		else
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("按照车主名查询失败！");
		}

		return;
	}

	GetDlgItemText(IDC_EDIT_QuserPhone,strTemp);
	if (!strTemp.IsEmpty())
	{
		m_strQueryKey = strTemp.operator LPCSTR();
		m_pQueryFunc = GetUserInfoByPhone;

		if (REPAIRCARINFOSAVEDB_SUCCESS == m_pQueryFunc(m_strQueryKey.c_str(),
			m_curPageIndex,
			MAX_QUERY_COUNT,
			m_userInfoVect,
			true))
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("按照电话查询成功！");
			UpdateDataInfo();
		}
		else
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("按照电话查询失败！");
		}

		return;
	}


	m_strQueryKey.clear();
	m_pQueryFunc = GetUserInfoByLicNumber;

	if (REPAIRCARINFOSAVEDB_SUCCESS == m_pQueryFunc(NULL,
		m_curPageIndex,
		MAX_QUERY_COUNT,
		m_userInfoVect,
		true))
	{
		CRepairCarInfoManageDlg::ShowOperateInfo("查询全部记录成功！");
		UpdateDataInfo();
	}
	else
	{
		CRepairCarInfoManageDlg::ShowOperateInfo("查询全部记录失败！");
	}
}


void CUserMngQueryDlg::OnBnClickedButtonQuserbefore()
{
	// TODO: Add your control notification handler code here
	if (m_curPageIndex)
	{
		m_userInfoVect.clear();
		--m_curPageIndex;
		if(REPAIRCARINFOSAVEDB_SUCCESS == m_pQueryFunc(m_strQueryKey.length()?m_strQueryKey.c_str():NULL,
			m_curPageIndex,
			MAX_QUERY_COUNT,
			m_userInfoVect,
			true))
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("查询上一页成功！");
			UpdateDataInfo();
		}
		else
		{
			++m_curPageIndex;
			CRepairCarInfoManageDlg::ShowOperateInfo("查询上一页失败！");
		}
	}
	else
	{
		CRepairCarInfoManageDlg::ShowOperateInfo("没有上一页，不能查询！");
	}
}


void CUserMngQueryDlg::OnBnClickedButtonQusernext()
{
	// TODO: Add your control notification handler code here
	if (m_userInfoVect.size()>=MAX_QUERY_COUNT)
	{
		m_userInfoVect.clear();
		++m_curPageIndex;
		if(REPAIRCARINFOSAVEDB_SUCCESS == m_pQueryFunc(m_strQueryKey.length()?m_strQueryKey.c_str():NULL,
			m_curPageIndex,
			MAX_QUERY_COUNT,
			m_userInfoVect,
			true))
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("查询下一页成功！");
			UpdateDataInfo();
		}
		else
		{
			--m_curPageIndex;
			CRepairCarInfoManageDlg::ShowOperateInfo("查询下一页失败！");
		}
	}
	else
	{
		CRepairCarInfoManageDlg::ShowOperateInfo("没有下一页，不能查询！");
	}
}


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
	OnSmenuUserdetail();

	*pResult = 0;
}


void CUserMngQueryDlg::OnSmenuUserdelete()
{
	// TODO: Add your command handler code here
	int selectIndex = m_userList.GetSelectionMark();
	if(selectIndex<0)
		return;

	if(IDYES== MessageBox("是否删除当前选中的维修信息?","提示",MB_YESNO))
	{
		CString strTemp = m_userList.GetItemText(selectIndex,0);
		if(REPAIRCARINFOSAVEDB_SUCCESS ==  DeleteUserInfoByLicNumber(strTemp.operator LPCSTR()))
		{
			m_userList.DeleteItem(selectIndex);
			CRepairCarInfoManageDlg::ShowOperateInfo("车主信息删除成功！");
		}
		else
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("车主信息删除失败！");
		}

	}
}


void CUserMngQueryDlg::OnSmenuUserdetail()
{
	// TODO: Add your command handler code here
	if(g_pMainDlg == NULL || m_userList.GetSelectedCount()<=0)
		return;

	int selectIndex = m_userList.GetSelectionMark();
	((CUserInfoDlg*)(g_pMainDlg->m_pages[IDD_USERMNG_MODIFY_DLG]))->SetOperateType(OPERATE_TYPE_SHOW,&m_userInfoVect[selectIndex]);
	g_pMainDlg->RightPageShow(IDD_USERMNG_MODIFY_DLG);
	CRepairCarInfoManageDlg::ShowOperateInfo("车主信息 - 详细内容！");
}


void CUserMngQueryDlg::OnSmenuUsermodify()
{
	// TODO: Add your command handler code here
	if(g_pMainDlg == NULL || m_userList.GetSelectedCount()<=0)
		return;

	int selectIndex = m_userList.GetSelectionMark();
	((CUserInfoDlg*)(g_pMainDlg->m_pages[IDD_USERMNG_MODIFY_DLG]))->SetOperateType(OPERATE_TYPE_MODIFY,&m_userInfoVect[selectIndex]);
	g_pMainDlg->RightPageShow(IDD_USERMNG_MODIFY_DLG);
	CRepairCarInfoManageDlg::ShowOperateInfo("车主信息 - 详细内容！");
}

void CUserMngQueryDlg::QueryUserInfoByLicNumber(const char* lpLicNumber)
{
	SetDlgItemText(IDC_EDIT_QuserLicNumber,lpLicNumber);
	SetDlgItemText(IDC_EDIT_QuserName,"");
	SetDlgItemText(IDC_EDIT_QuserPhone,"");

	OnBnClickedBtnUserUserquery();
}


void CUserMngQueryDlg::OnSmenuUserqueryrepair()
{
	// TODO: Add your command handler code here
	if(g_pMainDlg == NULL || m_userList.GetSelectedCount()<=0)
		return;

	int selectIndex = m_userList.GetSelectionMark();
	((CRepairInfoQueryDlg*)(g_pMainDlg->m_pages[IDD_MaintenanceMng_QUERY_Dlg]))->QueryRepairInfoByLicNumber(m_userInfoVect[selectIndex].csLicenseNumber);
	g_pMainDlg->RightPageShow(IDD_MaintenanceMng_QUERY_Dlg);
	CRepairCarInfoManageDlg::ShowOperateInfo("修车信息 - 详细内容！");
}

void CUserMngQueryDlg::UpdateDataInfo()
{
	m_userList.SetRedraw(FALSE);
	//更新内容
	m_userList.DeleteAllItems();

	int nRow;
	for(int i = 0 ; i < m_userInfoVect.size() ; ++i) 
	{ 
		nRow = m_userList.InsertItem(i, m_userInfoVect[i].csLicenseNumber);//插入行
		m_userList.SetItemText(nRow, 1, m_userInfoVect[i].csUserName);//设置数据
		m_userList.SetItemText(nRow, 2, m_userInfoVect[i].csUserPhone);
		m_userList.SetItemText(nRow, 3, m_userInfoVect[i].csUserAddress);
		m_userList.SetItemText(nRow, 4, m_userInfoVect[i].strUserReserve.c_str());
	} 

	m_userList.SetRedraw(TRUE);
	m_userList.Invalidate();
	m_userList.UpdateWindow();
}

BOOL CUserMngQueryDlg::PreTranslateMessage(MSG* pMsg)
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
			OnBnClickedBtnUserUserquery();
			return true;
		default:
			;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
