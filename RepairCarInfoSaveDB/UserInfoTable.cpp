#include "stdafx.h"
#include "UserInfoTable.h"


CUserInfoTable::CUserInfoTable(CDbBase* pBase)
	:CTableOperateBase(pBase)
{
}


CUserInfoTable::~CUserInfoTable(void)
{
}


int CUserInfoTable::InitTable()
{
	int iRes = SQLITE_OK;

	iRes = m_pDbBase->m_dbOp.get_table("UserInfo");
	if (SQLITE_OK != iRes)
	{
		const char* lpTableInfoSql = "CREATE TABLE UserInfo (licenseNumber TEXT PRIMARY KEY,userName TEXT, userPhone TEXT, userAddress TEXT,userReserve	TEXT);";
		iRes = m_pDbBase->m_dbOp.execute_dml(lpTableInfoSql);
	}

	return iRes;
}

int	CUserInfoTable::InsertUserInfo(PUserTableInfo	pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"insert into UserInfo values ('";
	sql<<pInfo->csLicenseNumber<<"','";
	sql<<pInfo->csUserName<<"','";
	sql<<pInfo->csUserPhone<<"','";
	sql<<pInfo->csUserAddress<<"','";
	sql<<pInfo->strUserReserve<<"');";
	char csUTF8[MAX_NUM_CHAR]={0};
	db_operator::ToUTF8(sql.str().c_str(),csUTF8);
	iRes = m_pDbBase->m_dbOp.execute(csUTF8, NULL, NULL, NULL);

	return iRes;
}

int	CUserInfoTable::UpdateUserInfo(PUserTableInfo	pInfo)
{
	int iRes = SQLITE_OK;
	bool bUp = false;
	sqlstring sql;

	sql<<"update UserInfo set ";
	if (strlen(pInfo->csUserName))
	{
		sql<<"userName='"<<pInfo->csUserName<<"'";
		bUp = true;
	}

	if (strlen(pInfo->csUserPhone))
	{
		if (bUp)
			sql<<",";
		sql<<"userPhone='"<<pInfo->csUserPhone<<"'";
		bUp = true;
	}

	if (strlen(pInfo->csUserAddress))
	{
		if (bUp)
			sql<<",";
		sql<<"userAddress='"<<pInfo->csUserAddress<<"'";
		bUp = true;
	}

	if (pInfo->strUserReserve.size())
	{
		if (bUp)
			sql<<",";
		sql<<"userReserve='"<<pInfo->strUserReserve<<"'";
		bUp = true;
	}

	sql<<" where licenseNumber='"<<pInfo->csLicenseNumber<<"';";
	
	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CUserInfoTable::GetUserInfoByLicNumber(const char* lpLicNumer,int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc/*=true*/)
{
	if (NULL == lpLicNumer||0 == strlen(lpLicNumer))
		return GetUserInfoAllData(iPages,iMaxCount,userInfoList,bOrderInc);

	sqlstring sql;
	sql<<"select * from UserInfo where  licenseNumber like '%";
	sql<<lpLicNumer<<"%' order by licenseNumber ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	return GetUserInfoData(sql.str().c_str(),userInfoList);
}

int CUserInfoTable::GetUserInfoByName(const char* lpName,int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc/*=true*/)
{
	if (NULL == lpName||0 == strlen(lpName))
		return GetUserInfoAllData(iPages,iMaxCount,userInfoList,bOrderInc);

	sqlstring sql;
	sql<<"select * from UserInfo where  userName like '%";
	sql<<lpName<<"%' order by licenseNumber ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	return GetUserInfoData(sql.str().c_str(),userInfoList);
}

int CUserInfoTable::GetUserInfoByPhone(const char* lpPhoneNumer,int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc/*=true*/)
{
	if (NULL == lpPhoneNumer||0 == strlen(lpPhoneNumer))
		return GetUserInfoAllData(iPages,iMaxCount,userInfoList,bOrderInc);

	sqlstring sql;
	sql<<"select * from UserInfo where  userPhone like '%";
	sql<<lpPhoneNumer<<"%' order by licenseNumber ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	return GetUserInfoData(sql.str().c_str(),userInfoList);
}

int CUserInfoTable::GetUserInfoAllData(int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc/*=true*/)
{
	sqlstring sql;
	sql<<"select * from UserInfo order by licenseNumber ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	return GetUserInfoData(sql.str().c_str(),userInfoList);
}

int CUserInfoTable::GetUserInfoData(const char* lpSql,std::vector<UserTableInfo>& userInfoList)
{
	return m_pDbBase->m_dbOp.execute(lpSql,CUserInfoTable::GetUserInfoDataHandle,&userInfoList,NULL);
}

int CUserInfoTable::GetUserInfoDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName)
{
	std::vector<UserTableInfo>* pUserList = (std::vector<UserTableInfo>*)lpPara;
	UserTableInfo tempUserInfo;

	char csUTF8[1024]={0};
	

	for (int i=0;i<nColumn;++i)
	{
		db_operator::ToGBK(lppColumnValue[i],csUTF8);
		if (0== strcmp(lppColumnName[i],"licenseNumber"))
		{
			strcpy(tempUserInfo.csLicenseNumber,csUTF8);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"userName"))
		{
			strcpy(tempUserInfo.csUserName,csUTF8);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"userPhone"))
		{
			strcpy(tempUserInfo.csUserPhone,csUTF8);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"userAddress"))
		{
			strcpy(tempUserInfo.csUserAddress,csUTF8);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"userReserve"))
		{
			tempUserInfo.strUserReserve = csUTF8;
		}
	}

	pUserList->push_back(tempUserInfo);

	return SQLITE_OK;
}

int	CUserInfoTable::DeleteUserInfoByLicNumber(const char* lpLicNumer)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"delete from UserInfo where licenseNumber='";
	sql<<lpLicNumer<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}