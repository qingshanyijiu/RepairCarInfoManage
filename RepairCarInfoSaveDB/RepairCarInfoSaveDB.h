#ifndef ___REPAIRCARINFOSAVEDB_____H
#define ___REPAIRCARINFOSAVEDB_____H

#include <string>
#include <list>

#ifdef REPAIRCARINFOSAVEDB_EXPORTS
#define REPAIRCARINFOSAVEDB_API __declspec(dllexport)
#else
#define REPAIRCARINFOSAVEDB_API __declspec(dllimport)
#endif

//**********************************************table info struct and define **************************************//

#define	REPAIRCARINFOSAVEDB_SUCCESS		(0)
#define	REPAIRCARINFOSAVEDB_ERROR		(1)

typedef	struct	tagUserTableInfo
{
	char		csLicenseNumber[16];
	char		csUserName[16];
	char		csUserPhone[16];
	char		csUserAddress[64];
	std::string	strUserReserve;

	tagUserTableInfo()
	{
		memset(csLicenseNumber,0,sizeof(csLicenseNumber));
		memset(csUserName,0,sizeof(csUserName));
		memset(csUserPhone,0,sizeof(csUserPhone));
		memset(csUserAddress,0,sizeof(csUserAddress));
		strUserReserve.clear();
	}

}UserTableInfo,*PUserTableInfo;

typedef	struct	tagRepairTableInfo
{
	char		csLicenseNumber[16];
	char		csRepairDate[16];		//YYYY-MM-DD
	std::string	strRepairNotes;
	std::string	strRepairReserve;

	tagRepairTableInfo()
	{
		memset(csLicenseNumber,0,sizeof(csLicenseNumber));
		memset(csRepairDate,0,sizeof(csRepairDate));
		strRepairNotes.clear();
		strRepairReserve.clear();
	}
}RepairTableInfo,*PRepairTableInfo;


//********************************************** Operate DB API	**************************************//

int REPAIRCARINFOSAVEDB_API OpenDb(const char* lpFileName);

int REPAIRCARINFOSAVEDB_API CloseDb();

int	REPAIRCARINFOSAVEDB_API InsertUserInfo(PUserTableInfo	pInfo);

int	REPAIRCARINFOSAVEDB_API UpdateUserInfo(PUserTableInfo	pInfo);

int REPAIRCARINFOSAVEDB_API GetUserInfoByLicNumber(const char* lpLicNumer,int iPages,int iMaxCount,std::list<UserTableInfo>& userInfoList,bool bOrderInc=true);

int REPAIRCARINFOSAVEDB_API GetUserInfoByName(const char* lpName,int iPages,int iMaxCount,std::list<UserTableInfo>& userInfoList,bool bOrderInc=true);

int REPAIRCARINFOSAVEDB_API GetUserInfoByPhone(const char* lpPhoneNumer,int iPages,int iMaxCount,std::list<UserTableInfo>& userInfoList,bool bOrderInc=true);

int	REPAIRCARINFOSAVEDB_API DeleteUserInfoByLicNumber(const char* lpLicNumer);

int	REPAIRCARINFOSAVEDB_API InsertRepairInfo(PRepairTableInfo	pInfo);

int	REPAIRCARINFOSAVEDB_API UpdateRepairInfo(PRepairTableInfo	pInfo);

int REPAIRCARINFOSAVEDB_API GetRepairInfoByLicNumber(const char* lpLicNumer,int iPages,int iMaxCount,std::list<RepairTableInfo>& repairInfoList,bool bOrderInc=true);

int REPAIRCARINFOSAVEDB_API GetRepairInfoByDate(const char* lpDate,int iPages,int iMaxCount,std::list<RepairTableInfo>& repairInfoList,bool bOrderInc=true);

int REPAIRCARINFOSAVEDB_API GetRepairInfoByDateRange(const char* lpBeinDate,const char* lpEndDate,int iPages,int iMaxCount,std::list<RepairTableInfo>& repairInfoList,bool bOrderInc=true);

int	REPAIRCARINFOSAVEDB_API DeleteRepairInfoByLicNumber(const char* lpLicNumer);



#endif