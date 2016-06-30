// RepairInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RepairCarInfoManage.h"
#include "RepairInfoDlg.h"
#include "afxdialogex.h"
#include "RepairCarInfoManageDlg.h"


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
	DDX_Control(pDX, IDC_EDIT_RepairDate, m_RepairDataEdit);
	DDX_Control(pDX, IDC_EDIT_RepairLicNumber, m_RepairLicNumber);
	DDX_Control(pDX, IDC_EDIT_RepairNotes, m_RepairNotes);
	DDX_Control(pDX, IDC_EDIT_RepairReserve, m_RepairReserve);
	DDX_Control(pDX, IDC_BTN_RepairAdd, m_AddModifyButton);
}


BEGIN_MESSAGE_MAP(CRepairInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_RepairAdd, &CRepairInfoDlg::OnBnClickedBtnRepairadd)
END_MESSAGE_MAP()


// CRepairInfoDlg message handlers


void CRepairInfoDlg::OnBnClickedBtnRepairadd()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CString	strTemp;

	GetDlgItemText(IDC_EDIT_RepairLicNumber,strTemp);
	strncpy(m_repairInfo.csLicenseNumber,strTemp.operator LPCSTR(),16);
	GetDlgItemText(IDC_EDIT_RepairDate,strTemp);
	strncpy(m_repairInfo.csRepairDate,strTemp.operator LPCSTR(),16);
	GetDlgItemText(IDC_EDIT_RepairNotes,strTemp);
	m_repairInfo.strRepairNotes = strTemp.operator LPCSTR();
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
}

void CRepairInfoDlg::SetOperateType(BYTE bType,PRepairTableInfo pInfo/*=NULL*/)
{
	m_RepairLicNumber.SetReadOnly(FALSE);
	m_bOperateType = bType;
	m_repairInfo.Clear();
	if(pInfo != NULL)
		m_repairInfo.Copy(*pInfo);
	switch(bType)
	{
	case OPERATE_TYPE_ADD:
		{
			SetDlgItemText(IDC_EDIT_RepairLicNumber,"");
			SetDlgItemText(IDC_EDIT_RepairDate,"");
			SetDlgItemText(IDC_EDIT_RepairNotes,"");
			SetDlgItemText(IDC_EDIT_RepairReserve,"");

			m_AddModifyButton.SetWindowText("增加");
			m_AddModifyButton.ShowWindow(SW_SHOW);
			m_repairInfo.Clear();
		}
		break;
	case OPERATE_TYPE_MODIFY:
	case OPERATE_TYPE_SHOW:

		SetDlgItemText(IDC_EDIT_RepairLicNumber,m_repairInfo.csLicenseNumber);
		SetDlgItemText(IDC_EDIT_RepairDate,m_repairInfo.csRepairDate);
		SetDlgItemText(IDC_EDIT_RepairNotes,m_repairInfo.strRepairNotes.c_str());
		SetDlgItemText(IDC_EDIT_userReserve,m_repairInfo.strRepairReserve.c_str());

		if(OPERATE_TYPE_MODIFY == m_bOperateType)
		{
			m_RepairLicNumber.SetReadOnly(TRUE);
			m_AddModifyButton.SetWindowText("修改");
			m_AddModifyButton.ShowWindow(SW_SHOW);
		}
		else
		{
			m_AddModifyButton.ShowWindow(SW_HIDE);
		}

		break;
	}
}


BOOL CRepairInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}
