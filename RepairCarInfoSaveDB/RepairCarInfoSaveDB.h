#ifndef ___REPAIRCARINFOSAVEDB_____H
#define ___REPAIRCARINFOSAVEDB_____H

#include <string>
#include <vector>

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
	char		csLicenseNumber[32];
	char		csUserName[32];
	char		csUserPhone[32];
	char		csUserAddress[64];
	std::string	strUserReserve;

	tagUserTableInfo()
	{
		Clear();
	}

	void Clear()
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
	int			iID;
	char		csLicenseNumber[32];
	char		csRepairDate[32];		//YYYY-MM-DD
	char		csRepairNextDate[32];
	std::string	strRepairNotes;
	std::string	strRepairItems;
	std::string	strRepairReserve;

	tagRepairTableInfo()
	{
		Clear();
	}

	void Clear(){
		iID =0;
		memset(csLicenseNumber,0,sizeof(csLicenseNumber));
		memset(csRepairDate,0,sizeof(csRepairDate));
		memset(csRepairNextDate,0,sizeof(csRepairNextDate));
		strRepairNotes.clear();
		strRepairItems.clear();
		strRepairReserve.clear();
	}

	void Copy(tagRepairTableInfo& info){
		iID = info.iID;
		strncpy(csLicenseNumber,info.csLicenseNumber,32);
		strncpy(csRepairDate,info.csRepairDate,32);
		strncpy(csRepairNextDate,info.csRepairNextDate,32);
		strRepairNotes = info.strRepairNotes;
		strRepairItems = info.strRepairItems;
		strRepairReserve = info.strRepairReserve;
	}
}RepairTableInfo,*PRepairTableInfo;


//********************************************** Operate DB API	**************************************//

int REPAIRCARINFOSAVEDB_API OpenDb(const char* lpFileName);

int REPAIRCARINFOSAVEDB_API CloseDb();

int	REPAIRCARINFOSAVEDB_API InsertUserInfo(PUserTableInfo	pInfo);

int	REPAIRCARINFOSAVEDB_API UpdateUserInfo(PUserTableInfo	pInfo);

int REPAIRCARINFOSAVEDB_API GetUserInfoByLicNumber(const char* lpLicNumer,int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc=true);

int REPAIRCARINFOSAVEDB_API GetUserInfoByName(const char* lpName,int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc=true);

int REPAIRCARINFOSAVEDB_API GetUserInfoByPhone(const char* lpPhoneNumer,int iPages,int iMaxCount,std::vector<UserTableInfo>& userInfoList,bool bOrderInc=true);

int	REPAIRCARINFOSAVEDB_API DeleteUserInfoByLicNumber(const char* lpLicNumer);

int	REPAIRCARINFOSAVEDB_API InsertRepairInfo(PRepairTableInfo	pInfo);

int	REPAIRCARINFOSAVEDB_API UpdateRepairInfo(PRepairTableInfo	pInfo);

int REPAIRCARINFOSAVEDB_API GetRepairInfo(const PRepairTableInfo const pInfo,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bFuzzyQuery=false,bool bOrderInc=true);

int REPAIRCARINFOSAVEDB_API GetRepairInfoByLicNumber(const char* lpLicNumer,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc=true);

int REPAIRCARINFOSAVEDB_API GetRepairInfoByDate(const char* lpDate,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc=true);

int REPAIRCARINFOSAVEDB_API GetRepairInfoByDateRange(const char* lpBeinDate,const char* lpEndDate,int iPages,int iMaxCount,std::vector<RepairTableInfo>& repairInfoList,bool bOrderInc=true);

int	REPAIRCARINFOSAVEDB_API DeleteRepairInfoByLicNumber(const char* lpLicNumer);

int	REPAIRCARINFOSAVEDB_API DeleteRepairInfoByID(int id);


#endif