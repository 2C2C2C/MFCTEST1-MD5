
// FkNp2bmfc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFkNp2bmfcApp: 
// �йش����ʵ�֣������ FkNp2bmfc.cpp
//

class CFkNp2bmfcApp : public CWinApp
{
public:
	CFkNp2bmfcApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFkNp2bmfcApp theApp;