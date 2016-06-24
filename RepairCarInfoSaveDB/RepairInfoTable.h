#pragma once

#include "TableOperateBase.h"
#include "SingletonInstance.h"

class CRepairInfoTable	
	:public	CTableOperateBase,public CSingletonInstance<CRepairInfoTable>
{
public:
	CRepairInfoTable(CDbBase* pBase);
	~CRepairInfoTable(void);

	void InitTable();
	

protected:

};

