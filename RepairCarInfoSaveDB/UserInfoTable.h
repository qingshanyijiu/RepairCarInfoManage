#pragma once

#include "TableOperateBase.h"
#include "SingletonInstance.h"

class CUserInfoTable	
	:public	CTableOperateBase,public CSingletonInstance<CUserInfoTable>
{
public:
	CUserInfoTable(CDbBase* pBase);
	~CUserInfoTable(void);

	void InitTable();
};

