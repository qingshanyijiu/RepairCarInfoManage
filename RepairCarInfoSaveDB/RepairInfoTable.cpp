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
		const char* lpTableInfoSql = "CREATE TABLE RepairInfo (id INT PRIMARY KEY,licenseNumber TEXT ,repairDate TEXT,repairNextDate TEXT, repairNotes TEXT,repairItems TEXT,repairReserve	TEXT);";
		iRes = m_pDbBase->m_dbOp.execute_dml(lpTableInfoSql);
	}

	return iRes;
}

int	CRepairInfoTable::InsertRepairInfo(PRepairTableInfo	pInfo)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"select max(id) from RepairInfo;";
	RetDataType RetData;
	if(m_pDbBase->QueryBySql(sql.str().c_str(),RetData))
	{
		sql.str("");
		sql<<"select count(*) from RepairInfo;";
		if (m_pDbBase->QueryBySql(sql.str().c_str(),RetData))
			return SQLITE_ERROR;
	}
	std::string maxidstr = *RetData[0].second.begin();
	if(maxidstr == "")
		maxidstr = "0";
	int maxid = atoi(maxidstr.c_str());
	sql.clear();
	sql.str("");
	sql<<"insert into RepairInfo values(";
	sql<<maxid+1<<",'";
	sql<<pInfo->csLicenseNumber<<"','";
	sql<<pInfo->csRepairDate<<"','";
	sql<<pInfo->csRepairNextDate<<"','";
	sql<<pInfo->strRepairNotes<<"','";
	sql<<pInfo->strRepairItems<<"','";
	sql<<pInfo->strRepairReserve<<"');";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int	CRepairInfoTable::UpdateRepairInfo(PRepairTableInfo	pInfo)
{
	int iRes = SQLITE_OK;
	bool bUp = false;
	sqlstring sql;

	sql<<"update RepairInfo set ";
	sql<<"licenseNumber='"<<pInfo->csLicenseNumber<<"',";
	sql<<"repairDate='"<<pInfo->csRepairDate<<"',";
	sql<<"repairNextDate='"<<pInfo->csRepairNextDate<<"',";
	sql<<"repairNotes='"<<pInfo->strRepairNotes<<"',";
	sql<<"repairItems='"<<pInfo->strRepairItems<<"',";
	sql<<"repairReserve='"<<pInfo->strRepairReserve<<"'";
	sql<<" where id="<<pInfo->iID<<";";
	/*
	if (pInfo->strRepairNotes.size())
	{
		sql<<"repairNotes='"<<pInfo->strRepairNotes<<"'";
		bUp = true;
	}

	if (pInfo->strRepairReserve.size())
	{
		if (bUp)
			sql<<",";
		sql<<"repairReserve='"<<pInfo->strRepairReserve<<"'";
		bUp = true;
	}

	sql<<" where licenseNumber='"<<pInfo->csLicenseNumber<<"'";
	sql<<" and repairDate='"<<pInfo->csRepairDate<<"';";*/

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CRepairInfoTable::GetRepairInfoByLicNumber(const char* lpLicNumer,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc/*=true*/)
{
	if (NULL == lpLicNumer||0 == strlen(lpLicNumer))
		return GetRepairInfoAllData(iPages,iMaxCount,repairInfoList,bOrderInc);

	sqlstring sql;
	sql<<"select * from RepairInfo where  licenseNumber ='";
	sql<<lpLicNumer<<"'order by licenseNumber ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	return GetRepairInfoData(sql.str().c_str(),repairInfoList);
}

int CRepairInfoTable::GetRepairInfo(const PRepairTableInfo const pInfo,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bFuzzyQuery/*=false*/,bool bOrderInc/* =true */)
{
	if (NULL == pInfo)
		return GetRepairInfoAllData(iPages,iMaxCount,repairInfoList,bOrderInc);

	sqlstring sql;
	sql<<"select * from RepairInfo where ";

	if(!bFuzzyQuery)
	{
		sql<<" licenseNumber ='"<<pInfo->csLicenseNumber<<"' and ";
		sql<<" repairDate ='"<<pInfo->csRepairDate<<"' and ";
		sql<<" repairNextDate ='"<<pInfo->csRepairNextDate<<"' and ";
		sql<<" repairNotes ='"<<pInfo->strRepairNotes.c_str()<<"' and ";
		sql<<" repairItems ='"<<pInfo->strRepairItems.c_str()<<"' and ";
		sql<<" repairReserve ='"<<pInfo->strRepairReserve.c_str()<<"' ";
	}
	else
	{
		sql<<" licenseNumber like '%"<<pInfo->csLicenseNumber<<"%' and ";
		sql<<" repairDate like '%"<<pInfo->csRepairDate<<"%' and ";
		sql<<" repairNextDate like '%"<<pInfo->csRepairNextDate<<"%' and ";
		sql<<" repairNotes like '%"<<pInfo->strRepairNotes.c_str()<<"%' and ";
		sql<<" repairItems like '%"<<pInfo->strRepairItems.c_str()<<"%' and ";
		sql<<" repairReserve like '%"<<pInfo->strRepairReserve.c_str()<<"%' ";
	}
	
	sql<<" order by licenseNumber ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql <<" and repairDate ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	return GetRepairInfoData(sql.str().c_str(),repairInfoList);
}

int CRepairInfoTable::GetRepairInfoByDate(const char* lpDate,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc/*=true*/)
{
	if (NULL == lpDate||0 == strlen(lpDate))
		return GetRepairInfoAllData(iPages,iMaxCount,repairInfoList,bOrderInc);

	sqlstring sql;
	sql<<"select * from RepairInfo where  repairDate ='";
	sql<<lpDate<<"'order by licenseNumber ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	return GetRepairInfoData(sql.str().c_str(),repairInfoList);
}

int CRepairInfoTable::GetRepairInfoByDateRange(const char* lpBeinDate,const char* lpEndDate,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc/*=true*/)
{
	if (NULL == lpBeinDate||0 == strlen(lpBeinDate)||NULL == lpEndDate||0 == strlen(lpEndDate))
		return GetRepairInfoAllData(iPages,iMaxCount,repairInfoList,bOrderInc);

	sqlstring sql;
	sql<<"select * from RepairInfo where  repairDate >='";
	sql<<lpBeinDate<<"' and repairDate <='"<<lpEndDate<<"'order by by licenseNumber ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	return GetRepairInfoData(sql.str().c_str(),repairInfoList);
}

int	CRepairInfoTable::DeleteRepairInfoByLicNumber(const char* lpLicNumer)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"delete from RepairInfo where licenseNumber='";
	sql<<lpLicNumer<<"';";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int	CRepairInfoTable::DeleteRepairInfoByID(int id)
{
	int iRes = SQLITE_OK;
	sqlstring sql;

	sql<<"delete from RepairInfo where id=";
	sql<<id<<";";

	iRes = m_pDbBase->m_dbOp.execute(sql.str().c_str(), NULL, NULL, NULL);

	return iRes;
}

int CRepairInfoTable::GetRepairInfoAllData(int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc/*=true*/)
{
	sqlstring sql;
	sql<<"select * from RepairInfo order by licenseNumber ";
	if (false == bOrderInc)
		sql<<"desc ";
	sql<<"limit "<<iMaxCount<<" offset "<<iMaxCount*iPages<<";";

	return GetRepairInfoData(sql.str().c_str(),repairInfoList);
}

int CRepairInfoTable::GetRepairInfoData(const char* lpSql,std::vector<RepairTableInfo>& repairInfoList)
{
	return m_pDbBase->m_dbOp.execute(lpSql,CRepairInfoTable::GetRepairInfoDataHandle,&repairInfoList,NULL);
}

int CRepairInfoTable::GetRepairInfoDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName)
{
	std::vector<RepairTableInfo>* pRepairList = (std::vector<RepairTableInfo>*)lpPara;
	RepairTableInfo tempInfo;

	for (int i=0;i<nColumn;++i)
	{
		if (0== strcmp(lppColumnName[i],"id"))
		{
			tempInfo.iID = atoi(lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"licenseNumber"))
		{
			strcpy(tempInfo.csLicenseNumber,lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"repairDate"))
		{
			strcpy(tempInfo.csRepairDate,lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"repairNextDate"))
		{
			strcpy(tempInfo.csRepairNextDate,lppColumnValue[i]);
			continue;
		}

		if (0== strcmp(lppColumnName[i],"repairNotes"))
		{
			tempInfo.strRepairNotes = lppColumnValue[i];
			continue;
		}

		if (0== strcmp(lppColumnName[i],"repairItems"))
		{
			tempInfo.strRepairItems = lppColumnValue[i];
			continue;
		}

		if (0== strcmp(lppColumnName[i],"repairReserve"))
		{
			tempInfo.strRepairReserve = lppColumnValue[i];
		}
	}

	pRepairList->push_back(tempInfo);

	return SQLITE_OK;
}