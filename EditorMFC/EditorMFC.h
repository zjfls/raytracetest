
// EditorMFC.h : EditorMFC Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CEditorMFCApp:
// �йش����ʵ�֣������ EditorMFC.cpp
//
#include "IListener.h"
class CEditorMFCApp : public CWinAppEx,public IListener
{
public:
	CEditorMFCApp();
	virtual ~CEditorMFCApp();




// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void OnNotify(string msg, IListenerSubject* pSubject);
// ʵ��
	COleTemplateServer m_server;
		// �����ĵ������ķ���������
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
	//virtual BOOL OnIdle(LONG lCount);
	virtual int		Run();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()


};

extern CEditorMFCApp theApp;
