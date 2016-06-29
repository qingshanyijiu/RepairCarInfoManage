// RepairCarInfoSaveImpl.h: interface for the CRepairCarInfoSaveImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPAIRCARINFOSAVEIMPL_H__DD0623E2_56C5_4225_91C5_DDCA939648DB__INCLUDED_)
#define AFX_REPAIRCARINFOSAVEIMPL_H__DD0623E2_56C5_4225_91C5_DDCA939648DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CriticalLock.h"
#include "DbBase.h"
#include "RepairInfoTable.h"
#include "UserInfoTable.h"

class CRepairCarInfoSaveImpl  
	:public CSingletonInstance<CRepairCarInfoSaveImpl>
{
public:
	CRepairCarInfoSaveImpl();
	virtual ~CRepairCarInfoSaveImpl();

	int OpenDb(const char* lpFileName);
	int CloseDb();

	int	InsertUserInfo(PUserTableInfo	pInfo);
	int	UpdateUserInfo(PUserTableInfo	pInfo);
	int GetUserInfoByLicNumber(const char* lpLicNumer,int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc=true);
	int GetUserInfoByName(const char* lpName,int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc=true);
	int GetUserInfoByPhone(const char* lpPhoneNumer,int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc=true);
	int	DeleteUserInfoByLicNumber(const char* lpLicNumer);

	int	InsertRepairInfo(PRepairTableInfo	pInfo);
	int	UpdateRepairInfo(PRepairTableInfo	pInfo);
	int GetRepairInfoByLicNumber(const char* lpLicNumer,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc=true);
	int GetRepairInfoByDate(const char* lpDate,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc=true);
	int GetRepairInfoByDateRange(const char* lpBeinDate,const char* lpEndDate,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc=true);
	int	DeleteRepairInfoByLicNumber(const char* lpLicNumer);

protected:
	CDbBase*				m_pDbBase;
	CUserInfoTable*			m_pUserTableOp;
	CRepairInfoTable*		m_pRepairTableOp;
	CCriticalLock			m_dbLock;
};

#endif // !defined(AFX_REPAIRCARINFOSAVEIMPL_H__DD0623E2_56C5_4225_91C5_DDCA939648DB__INCLUDED_)
