// RepairInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RepairCarInfoManage.h"
#include "RepairInfoDlg.h"
#include "afxdialogex.h"
#include "RepairCarInfoManageDlg.h"

extern CRepairCarInfoManageDlg*	g_pMainDlg;

// CRepairInfoDlg dialog

IMPLEMENT_DYNAMIC(CRepairInfoDlg, CDialogEx)

CRepairInfoDlg::CRepairInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRepairInfoDlg::IDD, pParent)
{

}

CRepairInfoDlg::~CRepairInfoDlg()
{
}

void CRepairInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RepairLicNumber, m_RepairLicNumber);
	DDX_Control(pDX, IDC_EDIT_RepairNotes, m_RepairNotes);
	DDX_Control(pDX, IDC_EDIT_RepairReserve, m_RepairReserve);
	DDX_Control(pDX, IDC_BTN_RepairAdd, m_AddModifyButton);
	DDX_Control(pDX, IDC_DATETIMEPICKER_Date, m_dateCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER_NextDate, m_nextDateCtrl);
}


BEGIN_MESSAGE_MAP(CRepairInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_RepairAdd, &CRepairInfoDlg::OnBnClickedBtnRepairadd)
END_MESSAGE_MAP()


// CRepairInfoDlg message handlers


void CRepairInfoDlg::OnBnClickedBtnRepairadd()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CString	strTemp;
	CTime   tempTime;

	GetDlgItemText(IDC_EDIT_RepairLicNumber,strTemp);
	strncpy(m_repairInfo.csLicenseNumber,strTemp.operator LPCSTR(),32);

	m_dateCtrl.GetTime(tempTime);
	strncpy(m_repairInfo.csRepairDate,tempTime.Format("%Y-%m-%d").operator LPCSTR(),32);

	m_nextDateCtrl.GetTime(tempTime);
	strncpy(m_repairInfo.csRepairNextDate,tempTime.Format("%Y-%m-%d").operator LPCSTR(),32);
	


	GetDlgItemText(IDC_EDIT_RepairNotes,strTemp);
	m_repairInfo.strRepairNotes = strTemp.operator LPCSTR();
	GetDlgItemText(IDC_EDIT_RepairItems,strTemp);
	m_repairInfo.strRepairItems= strTemp.operator LPCSTR();
	GetDlgItemText(IDC_EDIT_RepairReserve,strTemp);
	m_repairInfo.strRepairReserve = strTemp.operator LPCSTR();

	if (OPERATE_TYPE_ADD == m_bOperateType)
	{
		if(REPAIRCARINFOSAVEDB_SUCCESS == InsertRepairInfo(&m_repairInfo))
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("维修信息增加成功！");
		}
		else
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("维修信息增加失败！");
		}
	}
	else if (OPERATE_TYPE_MODIFY == m_bOperateType)
	{
		if(REPAIRCARINFOSAVEDB_SUCCESS == UpdateRepairInfo(&m_repairInfo))
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("维修信息修改成功！");
		}
		else
		{
			CRepairCarInfoManageDlg::ShowOperateInfo("维修信息修改失败！");
		}
	}
	else
	{
		g_pMainDlg->RightPageShow(IDD_MaintenanceMng_QUERY_Dlg);
	}
}

void CRepairInfoDlg::SetOperateType(BYTE bType,PRepairTableInfo pInfo/*=NULL*/)
{
	m_bOperateType = bType;
	m_repairInfo.Clear();
	if(pInfo != NULL)
		m_repairInfo.Copy(*pInfo);
	switch(bType)
	{
	case OPERATE_TYPE_ADD:
		{
			SetDlgItemText(IDC_EDIT_RepairLicNumber,"");

			m_dateCtrl.SetTime(&CTime::GetCurrentTime());
			CTimeSpan timespanOneMonth(180,0,0,0); //这里设置为当前日期推后180天 3
			CTime tEndTime =  CTime::GetCurrentTime() +timespanOneMonth;
			m_nextDateCtrl.SetTime(&tEndTime);

			SetDlgItemText(IDC_EDIT_RepairNotes,"");
			SetDlgItemText(IDC_EDIT_RepairItems,"");
			SetDlgItemText(IDC_EDIT_RepairReserve,"");

			m_AddModifyButton.SetWindowText("增加");
			m_repairInfo.Clear();
		}
		break;
	case OPERATE_TYPE_MODIFY:
	case OPERATE_TYPE_SHOW:
		{
			SetDlgItemText(IDC_EDIT_RepairLicNumber,m_repairInfo.csLicenseNumber);

			//CTime	tempTime;
			SYSTEMTIME	systemtime={0};
			sscanf(m_repairInfo.csRepairDate,"%d-%d-%d",&systemtime.wYear,&systemtime.wMonth,&systemtime.wDay);
			m_dateCtrl.SetTime(&systemtime);
			sscanf(m_repairInfo.csRepairNextDate,"%d-%d-%d",&systemtime.wYear,&systemtime.wMonth,&systemtime.wDay);
			m_nextDateCtrl.SetTime(&systemtime);

			SetDlgItemText(IDC_EDIT_RepairNotes,m_repairInfo.strRepairNotes.c_str());
			SetDlgItemText(IDC_EDIT_RepairItems,m_repairInfo.strRepairItems.c_str());
			SetDlgItemText(IDC_EDIT_RepairReserve,m_repairInfo.strRepairReserve.c_str());

			if(OPERATE_TYPE_MODIFY == m_bOperateType)
			{
				m_AddModifyButton.SetWindowText("修改");
			}
			else
			{
				m_AddModifyButton.SetWindowText("返回");
			}

		}
		

		break;
	}
}


BOOL CRepairInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	m_dateCtrl.SetTime(&CTime::GetCurrentTime());
	CTimeSpan timespanOneMonth(180,0,0,0); //这里设置为当前日期推后180天 3
	CTime tEndTime =  CTime::GetCurrentTime() +timespanOneMonth;
	m_nextDateCtrl.SetTime(&tEndTime);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


BOOL CRepairInfoDlg::PreTranslateMessage(MSG* pMsg)
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
			return true;
		default:
			;
		}
	}
	
	return CDialogEx::PreTranslateMessage(pMsg);
}
