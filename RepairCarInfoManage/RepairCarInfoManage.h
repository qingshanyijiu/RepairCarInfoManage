
// RepairCarInfoManage.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRepairCarInfoManageApp:
// �йش����ʵ�֣������ RepairCarInfoManage.cpp
//

class CRepairCarInfoManageApp : public CWinApp
{
public:
	CRepairCarInfoManageApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRepairCarInfoManageApp theApp;