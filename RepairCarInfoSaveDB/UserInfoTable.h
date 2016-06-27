#pragma once

#include "TableOperateBase.h"
#include "SingletonInstance.h"

class CUserInfoTable	
	:public	CTableOperateBase,public CSingletonInstance<CUserInfoTable>
{
public:
	CUserInfoTable(CDbBase* pBase);
	~CUserInfoTable(void);

	int InitTable();
	int	InsertUserInfo(PUserTableInfo	pInfo);
	int	UpdateUserInfo(PUserTableInfo	pInfo);
	int GetUserInfoByLicNumber(const char* lpLicNumer,int iPages,int iMaxCount,std::list<UserTableInfo>& userInfoList,bool bOrderInc=true);
	int GetUserInfoByName(const char* lpName,int iPages,int iMaxCount,std::list<UserTableInfo>& userInfoList,bool bOrderInc=true);
	int GetUserInfoByPhone(const char* lpPhoneNumer,int iPages,int iMaxCount,std::list<UserTableInfo>& userInfoList,bool bOrderInc=true);
	int	DeleteUserInfoByLicNumber(const char* lpLicNumer);

protected:
	int GetUserInfoAllData(int iPages,int iMaxCount,std::list<UserTableInfo>& userInfoList,bool bOrderInc=true);
	int GetUserInfoData(const char* lpSql,std::list<UserTableInfo>& userInfoList);

protected:
	static int GetUserInfoDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName);
};

