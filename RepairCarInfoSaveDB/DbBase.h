#pragma once

#include "dba.h"
#include "SingletonInstance.h"

class CDbBase : public CSingletonInstance<CDbBase>
{
public:
	CDbBase(void);
	~CDbBase(void);

public:

};

