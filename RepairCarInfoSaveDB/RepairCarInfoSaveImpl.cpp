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
	m_pDbBase			= NULL;
	m_pUserTableOp		= NULL;
	m_pRepairTableOp	= NULL;
}

CRepairCarInfoSaveImpl::~CRepairCarInfoSaveImpl()
{

}

int CRepairCarInfoSaveImpl::OpenDb(const char* lpFileName)
{
	CCriticalLock::CAutoLock lock(m_dbLock);
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
	if (NULL == m_pDbBase)
		return REPAIRCARINFOSAVEDB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pDbBase->CloseDb();
}

int	CRepairCarInfoSaveImpl::InsertUserInfo(PUserTableInfo	pInfo)
{
	if (NULL == m_pUserTableOp)
		return REPAIRCARINFOSAVEDB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pUserTableOp->InsertUserInfo(pInfo);
}

int	CRepairCarInfoSaveImpl::UpdateUserInfo(PUserTableInfo	pInfo)
{
	if (NULL == m_pUserTableOp)
		return REPAIRCARINFOSAVEDB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pUserTableOp->UpdateUserInfo(pInfo);
}

int CRepairCarInfoSaveImpl::GetUserInfoByLicNumber(const char* lpLicNumer,int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc/*=true*/)
{
	if (NULL == m_pUserTableOp)
		return REPAIRCARINFOSAVEDB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pUserTableOp->GetUserInfoByLicNumber(lpLicNumer,iPages,iMaxCount,userInfoList,bOrderInc);
}

int CRepairCarInfoSaveImpl::GetUserInfoByName(const char* lpName,int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc/*=true*/)
{
	if (NULL == m_pUserTableOp)
		return REPAIRCARINFOSAVEDB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pUserTableOp->GetUserInfoByName(lpName,iPages,iMaxCount,userInfoList,bOrderInc);
}

int CRepairCarInfoSaveImpl::GetUserInfoByPhone(const char* lpPhoneNumer,int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc/*=true*/)
{
	if (NULL == m_pUserTableOp)
		return REPAIRCARINFOSAVEDB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pUserTableOp->GetUserInfoByPhone(lpPhoneNumer,iPages,iMaxCount,userInfoList,bOrderInc);
}

int	CRepairCarInfoSaveImpl::DeleteUserInfoByLicNumber(const char* lpLicNumer)
{
	if (NULL == m_pUserTableOp)
		return REPAIRCARINFOSAVEDB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pUserTableOp->DeleteUserInfoByLicNumber(lpLicNumer);
}

int	CRepairCarInfoSaveImpl::InsertRepairInfo(PRepairTableInfo	pInfo)
{
	if (NULL == m_pRepairTableOp)
		return REPAIRCARINFOSAVEDB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pRepairTableOp->InsertRepairInfo(pInfo);
}

int	CRepairCarInfoSaveImpl::UpdateRepairInfo(PRepairTableInfo	pInfo)
{
	if (NULL == m_pRepairTableOp)
		return REPAIRCARINFOSAVEDB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pRepairTableOp->UpdateRepairInfo(pInfo);
}

int CRepairCarInfoSaveImpl::GetRepairInfoByLicNumber(const char* lpLicNumer,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc/*=true*/)
{
	if (NULL == m_pRepairTableOp)
		return REPAIRCARINFOSAVEDB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pRepairTableOp->GetRepairInfoByLicNumber(lpLicNumer,iPages,iMaxCount,repairInfoList,bOrderInc);
}

int CRepairCarInfoSaveImpl::GetRepairInfo(const PRepairTableInfo const pInfo,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bFuzzyQuery/*=false*/,bool bOrderInc/* =true */)
{
	if (NULL == m_pRepairTableOp)
		return REPAIRCARINFOSAVEDB_ERROR;
	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pRepairTableOp->GetRepairInfo(pInfo,iPages,iMaxCount,repairInfoList,bFuzzyQuery,bOrderInc);
}

int CRepairCarInfoSaveImpl::GetRepairInfoByDate(const char* lpDate,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc/*=true*/)
{
	if (NULL == m_pRepairTableOp)
		return REPAIRCARINFOSAVEDB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pRepairTableOp->GetRepairInfoByDate(lpDate,iPages,iMaxCount,repairInfoList,bOrderInc);
}

int CRepairCarInfoSaveImpl::GetRepairInfoByDateRange(const char* lpBeinDate,const char* lpEndDate,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc/*=true*/)
{
	if (NULL == m_pRepairTableOp)
		return REPAIRCARINFOSAVEDB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pRepairTableOp->GetRepairInfoByDateRange(lpBeinDate,lpEndDate,iPages,iMaxCount,repairInfoList,bOrderInc);
}

int	CRepairCarInfoSaveImpl::DeleteRepairInfoByLicNumber(const char* lpLicNumer)
{
	if (NULL == m_pRepairTableOp)
		return REPAIRCARINFOSAVEDB_ERROR;

	CCriticalLock::CAutoLock lock(m_dbLock);
	return m_pRepairTableOp->DeleteRepairInfoByLicNumber(lpLicNumer);
}