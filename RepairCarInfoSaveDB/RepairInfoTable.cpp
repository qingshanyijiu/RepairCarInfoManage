#include "stdafx.h"
#include "RepairInfoTable.h"


CRepairInfoTable::CRepairInfoTable(CDbBase* pBase)
	:CTableOperateBase(pBase)
{
}


CRepairInfoTable::~CRepairInfoTable(void)
{
}


int CRepairInfoTable::InitTable()
{
	int iRes = SQLITE_OK;

	iRes = m_pDbBase->m_dbOp.get_table("RepairInfo");
	if (SQLITE_OK != iRes)
	{
		const char* lpTableInfoSql = "CREATE TABLE RepairInfo (licenseNumber TEXT PRIMARY KEY,repairDate TEXT, repairNotes TEXT,repairReserve	TEXT);";
		iRes = m_pDbBase->m_dbOp.execute_dml(lpTableInfoSql);
	}

	return iRes;
}