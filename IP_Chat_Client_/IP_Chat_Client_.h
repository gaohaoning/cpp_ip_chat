
// IP_Chat_Client_.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIP_Chat_Client_App:
// �йش����ʵ�֣������ IP_Chat_Client_.cpp
//

class CIP_Chat_Client_App : public CWinAppEx
{
public:
	CIP_Chat_Client_App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIP_Chat_Client_App theApp;