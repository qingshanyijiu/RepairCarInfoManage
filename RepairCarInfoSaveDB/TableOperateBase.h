#pragma once

#include "DbBase.h"

class CTableOperateBase
{
public:
	CTableOperateBase(CDbBase* pBase);
	virtual ~CTableOperateBase(void);

	virtual void InitTable() = 0;

protected:
	CDbBase*	m_pDbBase;
};

