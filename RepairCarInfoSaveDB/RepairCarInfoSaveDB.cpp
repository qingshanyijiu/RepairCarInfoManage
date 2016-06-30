// RepairCarInfoSaveDB.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "RepairCarInfoSaveDB.h"
#include "SingletonInstance.h"
#include "RepairCarInfoSaveImpl.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

int REPAIRCARINFOSAVEDB_API OpenDb(const char* lpFileName)
{
	return CRepairCarInfoSaveImpl::GetInstance()->OpenDb(lpFileName);
}

int REPAIRCARINFOSAVEDB_API CloseDb()
{
	return CRepairCarInfoSaveImpl::GetInstance()->CloseDb();
}

int	REPAIRCARINFOSAVEDB_API InsertUserInfo(PUserTableInfo	pInfo)
{
	return  CRepairCarInfoSaveImpl::GetInstance()->InsertUserInfo(pInfo);
}

int	REPAIRCARINFOSAVEDB_API UpdateUserInfo(PUserTableInfo	pInfo)
{
	return CRepairCarInfoSaveImpl::GetInstance()->UpdateUserInfo(pInfo);
}

int REPAIRCARINFOSAVEDB_API GetUserInfoByLicNumber(const char* lpLicNumer,int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc/*=true*/)
{
	return CRepairCarInfoSaveImpl::GetInstance()->GetUserInfoByLicNumber(lpLicNumer,iPages,iMaxCount,userInfoList,bOrderInc);
}

int REPAIRCARINFOSAVEDB_API GetUserInfoByName(const char* lpName,int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc/*=true*/)
{
	return CRepairCarInfoSaveImpl::GetInstance()->GetUserInfoByLicNumber(lpName,iPages,iMaxCount,userInfoList,bOrderInc);
}

int REPAIRCARINFOSAVEDB_API GetUserInfoByPhone(const char* lpPhoneNumer,int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc/*=true*/)
{
	return CRepairCarInfoSaveImpl::GetInstance()->GetUserInfoByPhone(lpPhoneNumer,iPages,iMaxCount,userInfoList,bOrderInc);
}

int	REPAIRCARINFOSAVEDB_API DeleteUserInfoByLicNumber(const char* lpLicNumer)
{
	return CRepairCarInfoSaveImpl::GetInstance()->DeleteUserInfoByLicNumber(lpLicNumer);
}

int	REPAIRCARINFOSAVEDB_API InsertRepairInfo(PRepairTableInfo	pInfo)
{
	return CRepairCarInfoSaveImpl::GetInstance()->InsertRepairInfo(pInfo);
}

int	REPAIRCARINFOSAVEDB_API UpdateRepairInfo(PRepairTableInfo	pInfo)
{
	return CRepairCarInfoSaveImpl::GetInstance()->UpdateRepairInfo(pInfo);
}

int REPAIRCARINFOSAVEDB_API GetRepairInfoByLicNumber(const char* lpLicNumer,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc/*=true*/)
{
	return CRepairCarInfoSaveImpl::GetInstance()->GetRepairInfoByLicNumber(lpLicNumer,iPages,iMaxCount,repairInfoList,bOrderInc);
}

int REPAIRCARINFOSAVEDB_API GetRepairInfo(const PRepairTableInfo const pInfo,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bFuzzyQuery/*=false*/,bool bOrderInc/* =true */)
{
	return CRepairCarInfoSaveImpl::GetInstance()->GetRepairInfo(pInfo,iPages,iMaxCount,repairInfoList,bFuzzyQuery,bOrderInc);
}

int REPAIRCARINFOSAVEDB_API GetRepairInfoByDate(const char* lpDate,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc/*=true*/)
{
	return CRepairCarInfoSaveImpl::GetInstance()->GetRepairInfoByDate(lpDate,iPages,iMaxCount,repairInfoList,bOrderInc);
}

int REPAIRCARINFOSAVEDB_API GetRepairInfoByDateRange(const char* lpBeinDate,const char* lpEndDate,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc/*=true*/)
{
	return CRepairCarInfoSaveImpl::GetInstance()->GetRepairInfoByDateRange(lpBeinDate,lpEndDate,iPages,iMaxCount,repairInfoList,bOrderInc);
}

int	REPAIRCARINFOSAVEDB_API DeleteRepairInfoByLicNumber(const char* lpLicNumer)
{
	return CRepairCarInfoSaveImpl::GetInstance()->DeleteRepairInfoByLicNumber(lpLicNumer);
}

int	REPAIRCARINFOSAVEDB_API DeleteRepairInfoByID(int id)
{
	return CRepairCarInfoSaveImpl::GetInstance()->DeleteRepairInfoByID(id);
}