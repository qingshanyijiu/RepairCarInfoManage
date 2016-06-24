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