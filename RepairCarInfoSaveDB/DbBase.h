#pragma once

#include "dba.h"
#include "SingletonInstance.h"
#include <string>
#include "CriticalLock.h"

class CDbBase : public CSingletonInstance<CDbBase>
{
public:
	CDbBase(void);
	~CDbBase(void);

	int OpenDb(const char* lpFileName);
	int CloseDb();

protected:
	static void GetThisDllPath(std::string& strPath);

public:
	CCriticalLock	m_dbLock;
	db_operator		m_dbOp;

protected:
	bool			m_bIsOpen;
};

