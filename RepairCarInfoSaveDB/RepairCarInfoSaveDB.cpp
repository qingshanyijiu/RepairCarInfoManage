// RepairCarInfoSaveDB.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "RepairCarInfoSaveDB.h"
#include "RepairCarInfoSaveImpl.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

template<typename DataType>
class CSingleInstance
{
public:
	CSingleInstance()
	{
		m_pInstance = NULL;
	}
	~CSingleInstance()
	{
		if (NULL != m_pInstance)
			delete m_pInstance;
	}
	
	void Set(DataType* pInstance)
	{
		if (m_pInstance)
			delete m_pInstance;
		m_pInstance = pInstance;
	}
	
public:
	DataType*	m_pInstance;	
};

static CSingleInstance<CRepairCarInfoSaveImpl>	m_ImplInstance;

int REPAIRCARINFOSAVEDB_API OpenDb(const char* lpFileName)
{
	if (NULL == m_ImplInstance.m_pInstance)
		m_ImplInstance.Set(new CRepairCarInfoSaveImpl());

	return m_ImplInstance.m_pInstance->OpenDb(lpFileName);
}

int REPAIRCARINFOSAVEDB_API CloseDb()
{
	if (NULL == m_ImplInstance.m_pInstance)
		return REPAIRCARINFOSAVEDB_ERROR;

	return m_ImplInstance.m_pInstance->CloseDb();
}