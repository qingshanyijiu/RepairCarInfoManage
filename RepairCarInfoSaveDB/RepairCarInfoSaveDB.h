#ifndef ___REPAIRCARINFOSAVEDB_____H
#define ___REPAIRCARINFOSAVEDB_____H

#ifdef REPAIRCARINFOSAVEDB_EXPORTS
#define REPAIRCARINFOSAVEDB_API __declspec(dllexport)
#else
#define REPAIRCARINFOSAVEDB_API __declspec(dllimport)
#endif


#define	REPAIRCARINFOSAVEDB_SUCCESS		(0)
#define	REPAIRCARINFOSAVEDB_ERROR		(1)
	

int REPAIRCARINFOSAVEDB_API OpenDb(const char* lpFileName);

int REPAIRCARINFOSAVEDB_API CloseDb();





#endif