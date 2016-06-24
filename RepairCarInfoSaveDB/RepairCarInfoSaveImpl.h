// RepairCarInfoSaveImpl.h: interface for the CRepairCarInfoSaveImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPAIRCARINFOSAVEIMPL_H__DD0623E2_56C5_4225_91C5_DDCA939648DB__INCLUDED_)
#define AFX_REPAIRCARINFOSAVEIMPL_H__DD0623E2_56C5_4225_91C5_DDCA939648DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRepairCarInfoSaveImpl  
{
public:
	CRepairCarInfoSaveImpl();
	virtual ~CRepairCarInfoSaveImpl();

	int OpenDb(const char* lpFileName);
	int CloseDb();


};

#endif // !defined(AFX_REPAIRCARINFOSAVEIMPL_H__DD0623E2_56C5_4225_91C5_DDCA939648DB__INCLUDED_)
