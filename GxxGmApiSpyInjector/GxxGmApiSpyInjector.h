
// GxxGmApiSpyInjector.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGxxGmApiSpyInjectorApp: 
// �йش����ʵ�֣������ GxxGmApiSpyInjector.cpp
//

class CGxxGmApiSpyInjectorApp : public CWinApp
{
public:
	CGxxGmApiSpyInjectorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGxxGmApiSpyInjectorApp theApp;