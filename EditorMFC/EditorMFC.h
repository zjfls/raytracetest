
// EditorMFC.h : EditorMFC 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CEditorMFCApp:
// 有关此类的实现，请参阅 EditorMFC.cpp
//
#include "IListener.h"
class CEditorMFCApp : public CWinAppEx,public IListener
{
public:
	CEditorMFCApp();
	virtual ~CEditorMFCApp();




// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void OnNotify(string msg, IListenerSubject* pSubject);
// 实现
	COleTemplateServer m_server;
		// 用于文档创建的服务器对象
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
