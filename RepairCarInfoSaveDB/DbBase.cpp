#include "stdafx.h"
#include "DbBase.h"
#include "Dbghelp.h"

#pragma comment(lib,"Dbghelp.lib")


#ifdef _DEBUG
#define DB_LIB_PATH "RepairCarInfoSaveDBD.dll"
#else
#define DB_LIB_PATH "RepairCarInfoSaveDB.dll"
#endif

CDbBase::CDbBase(void)
{
	m_bIsOpen = false;
}


CDbBase::~CDbBase(void)
{
	CloseDb();
}


int CDbBase::OpenDb(const char* lpFileName)
{
	if(m_bIsOpen)
		return REPAIRCARINFOSAVEDB_SUCCESS;

	string strPath = lpFileName;
	if (string::npos == strPath.find(':'))
	{
		GetThisDllPath(strPath);
		strPath +="SaveInfo\\";
		strPath += lpFileName;
	}
	MakeSureDirectoryPathExists(strPath.c_str());

	int iRes = m_dbOp.open(strPath.c_str());
	if (SQLITE_OK == iRes)
		m_bIsOpen = true;

	return iRes;
}

int CDbBase::CloseDb()
{
	int iRes  = SQLITE_OK;
	if (m_bIsOpen)
	{
		iRes = m_dbOp.close();
		if (SQLITE_OK == iRes)
			m_bIsOpen  = false;
	}

	return iRes;
}

void CDbBase::GetThisDllPath(std::string& strPath)
{
	CHAR tcDllPath[MAX_PATH]={0};

	::GetModuleFileName(::GetModuleHandle(DB_LIB_PATH),tcDllPath,MAX_PATH);
	strPath = tcDllPath;

	int iPos = strPath.rfind('\\');
	if (string::npos != iPos)
		strPath = strPath.substr(0,iPos+1);
	else
		strPath.empty();
}