// RepairCarInfoSaveImpl.cpp: implementation of the CRepairCarInfoSaveImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RepairCarInfoSaveImpl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRepairCarInfoSaveImpl::CRepairCarInfoSaveImpl()
{

}

CRepairCarInfoSaveImpl::~CRepairCarInfoSaveImpl()
{

}

int CRepairCarInfoSaveImpl::OpenDb(const char* lpFileName)
{
	m_pDbBase			= CDbBase::GetInstance();
	m_pUserTableOp		= CUserInfoTable::GetInstance(m_pDbBase);
	m_pRepairTableOp	= CRepairInfoTable::GetInstance(m_pDbBase);

	int iRes = m_pDbBase->OpenDb(lpFileName);
	if (SQLITE_OK == iRes)
	{
		m_pUserTableOp->InitTable();
		m_pRepairTableOp->InitTable();
	}

	return iRes;
}

int CRepairCarInfoSaveImpl::CloseDb()
{
	return m_pDbBase->CloseDb();
}