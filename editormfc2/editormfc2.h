
// editormfc2.h : editormfc2 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// Ceditormfc2App:
// �йش����ʵ�֣������ editormfc2.cpp
//

class Ceditormfc2App : public CWinAppEx
{
public:
	Ceditormfc2App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	COleTemplateServer m_server;
		// �����ĵ������ķ���������
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ceditormfc2App theApp;
