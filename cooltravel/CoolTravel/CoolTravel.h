
// CoolTravel.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������



// CCoolTravelApp:
// �йش����ʵ�֣������ CoolTravel.cpp
//

class CCoolTravelApp : public CWinApp
{
public:
	CCoolTravelApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCoolTravelApp theApp;