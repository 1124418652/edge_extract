
// edge_extract.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cedge_extractApp: 
// �йش����ʵ�֣������ edge_extract.cpp
//

class Cedge_extractApp : public CWinApp
{
public:
	Cedge_extractApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cedge_extractApp theApp;