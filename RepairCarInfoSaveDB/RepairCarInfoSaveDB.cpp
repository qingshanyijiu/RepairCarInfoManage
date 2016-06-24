// RepairCarInfoSaveDB.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "RepairCarInfoSaveDB.h"
#include "SingletonInstance.h"
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

int REPAIRCARINFOSAVEDB_API OpenDb(const char* lpFileName)
{
	return CSingletonInstance<CRepairCarInfoSaveImpl>::GetInstance()->OpenDb(lpFileName);
}

int REPAIRCARINFOSAVEDB_API CloseDb()
{
	return CSingletonInstance<CRepairCarInfoSaveImpl>::GetInstance()->CloseDb();
}