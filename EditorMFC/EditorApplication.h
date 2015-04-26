#pragma once
#pragma once
#include "Singleton.h"
#include "ApplicationBase.h"
#include <map>
class EditorRenderView;
//class RenderView;
//
class EditorApplication:public ApplicationBase,public Singleton<EditorApplication>
{
public:
	EditorApplication();
	virtual ~EditorApplication();


	void SetWindowID(int id){ m_RenderViewInfo.m_windowID = id; m_nWindowID = id; };
	int		GetWindowID(){ return m_RenderViewInfo.m_bWindowed; };
	bool	AddView(int id,EditorRenderView*);
	bool	RemoveView(int id);

	void	Run();
	std::map<int, EditorRenderView*> m_ViewMap;
	//RenderView* CreateRenderView(int WindowID);
	virtual void SetupScene();
public:
	int m_nWindowID;
};

