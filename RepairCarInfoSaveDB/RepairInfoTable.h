#pragma once

#include "TableOperateBase.h"
#include "SingletonInstance.h"

class CRepairInfoTable	
	:public	CTableOperateBase,public CSingletonInstance<CRepairInfoTable>
{
public:
	CRepairInfoTable(CDbBase* pBase);
	~CRepairInfoTable(void);

	int InitTable();
	int	InsertRepairInfo(PRepairTableInfo	pInfo);
	int	UpdateRepairInfo(PRepairTableInfo	pInfo);
	int GetRepairInfoByLicNumber(const char* lpLicNumer,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc=true);
	int GetRepairInfoByDate(const char* lpDate,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc=true);
	int GetRepairInfoByDateRange(const char* lpBeinDate,const char* lpEndDate,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc=true);
	int	DeleteRepairInfoByLicNumber(const char* lpLicNumer);

protected:
	int GetRepairInfoAllData(int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc=true);
	int GetRepairInfoData(const char* lpSql,std::vector<RepairTableInfo>& repairInfoList);

protected:
	static int GetRepairInfoDataHandle(void * lpPara, int nColumn, char ** lppColumnValue, char ** lppColumnName);

};

