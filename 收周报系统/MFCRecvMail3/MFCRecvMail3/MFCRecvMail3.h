
// MFCRecvMail3.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCRecvMail3App: 
// �йش����ʵ�֣������ MFCRecvMail3.cpp
//

class CMFCRecvMail3App : public CWinApp
{
public:
	CMFCRecvMail3App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCRecvMail3App theApp;