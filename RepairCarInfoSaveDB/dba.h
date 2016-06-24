#ifndef __KT_CASHUNITINFO_DBA_INCLUDED_H__
#define __KT_CASHUNITINFO_DBA_INCLUDED_H__

extern "C"
{
#include "../ktdb/sqlite3.h"
#include "../ktdb/sqliteLimit.h"
};

#include <vector>
#include <sstream>
#include <string>
using namespace std;


#ifdef _DEBUG
#pragma comment(lib, "..\\lib\\ktdbD.lib")
#else
#pragma comment(lib, "..\\lib\\ktdb.lib")
#endif

typedef std::ostringstream sqlstring;

//ascii 转 utf-8
class a2u8
{
public:
	explicit a2u8(const char * str):u8(0)
	{
		//转成unicode
		int len=strlen(str);
		int unicodeLen=MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
		wchar_t* pUnicode = new wchar_t[unicodeLen+1];
		memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, 0, str, -1, (LPWSTR)pUnicode, unicodeLen);

		//utf-8
		BYTE * pTargetData=0;
		int targetLen=WideCharToMultiByte(CP_UTF8 , 0, (LPWSTR)pUnicode, -1, (char *)pTargetData, 0, NULL, NULL);
		pTargetData=new BYTE[targetLen+1];
		memset(pTargetData, 0, targetLen+1);
		WideCharToMultiByte(CP_UTF8,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,targetLen,NULL,NULL);

		//复制到
		u8 = new TCHAR[targetLen+1];
		memset(u8, 0, targetLen+1);
		wsprintf(u8,"%s",pTargetData);
		
		delete[] pUnicode;
		delete[] pTargetData;
	}

	~a2u8(){delete [] u8;}

	operator const char *()const {return u8;} 
private:
	a2u8();
	a2u8& operator=(const a2u8&);

private:
	char * u8;
};


class db_operator
{
public:
	db_operator():p_db_(0)
	{
	}
	~db_operator()
	{
	}

	int open(const char * filename)
	{
		db_file_name_ = filename;
		int res = sqlite3_open(a2u8(db_file_name_.c_str()), &p_db_);
		if (SQLITE_OK==res)
		{
		}

		return res;

	}

	int close()
	{
		int res = sqlite3_close(p_db_);
		if (SQLITE_OK==res) p_db_=0;

		return res;
	}

	int execute_dml(const char *sql)
	{
		int res = SQLITE_OK;
		do
		{
			res = sqlite3_exec(p_db_, sql, 0, 0, 0);
			
		}while((SQLITE_BUSY==res)||(SQLITE_LOCKED==res));
		
		return res;
	}

	int begin_trans()
	{
		const char * sql = "begin transaction;";

		return execute(sql, NULL, NULL, NULL);
		
	}

	int rollback_trans()
	{
		const char * sql = "rollback transaction;";

		return execute(sql, NULL, NULL, NULL);
		
	}

	int commit_trans()
	{
		const char * sql = "commit transaction;";

		return execute(sql, NULL, NULL, NULL);
		
	}

	int execute(const char *sql, sqlite3_callback cb, void * para, char **errmsg)
	{
		return sqlite3_exec(p_db_, sql, cb, para, errmsg);
	}

	static int query_table_name_handle(void * para, int n_column, char ** column_value, char ** column_name)
	{
		if(strlen(column_value[0]))
			memcpy(para, column_value[0], strlen(column_value[0]));

		return SQLITE_OK;
	}

	//SQLITE_OK 为有表，其它值为无表
	int get_table(const char * name)
	{
		sqlstring sql;
		sql << "select name from sqlite_master where type='table' and name='" << name << "';";
		char result[256]={0};

		int res = sqlite3_exec(p_db_, sql.str().c_str(), db_operator::query_table_name_handle, result, NULL);
		if (SQLITE_OK==res)
		{
			if (strcmp(name, result)) res=SQLITE_NOTFOUND;
		}
	
		return res;
	}


private:
	db_operator(const db_operator&);
	db_operator& operator=(const db_operator&);

	string db_file_name_;
	struct sqlite3 * p_db_;
};
#endif