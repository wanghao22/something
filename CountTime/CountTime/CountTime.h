
// CountTime.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCountTimeApp: 
// �йش����ʵ�֣������ CountTime.cpp
//

class CCountTimeApp : public CWinApp
{
public:
	CCountTimeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCountTimeApp theApp;