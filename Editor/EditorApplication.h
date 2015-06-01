#pragma once
#pragma once
#include "Singleton.h"
#include "ApplicationBase.h"
#include <map>
#include "IListenerSubject.h"
class IWorldObj;
class EditorRenderView;
//class RenderView;
//

class EDITOR_API EditorApplication :public ApplicationBase, public Singleton<EditorApplication>, public IListenerSubject,public GameObjectBase
{
public:
	EditorApplication();
	virtual ~EditorApplication();


	void	SetWindowID(int id){ m_RenderViewInfo.m_windowID = id; m_nWindowID = id; };
	int		GetWindowID(){ return m_RenderViewInfo.m_bWindowed; };
	bool	AddView(int id,EditorRenderView*);
	bool	RemoveView(int id);

	void	Run();
	std::map<int, EditorRenderView*> m_ViewMap;
	//RenderView* CreateRenderView(int WindowID);
	virtual void SetupScene();
	virtual void NotifyListener(std::string msg, IListenerSubject* pSubject);
	//
	void	OnSelectChange(SmartPointer<IWorldObj> pObj);

	virtual void OnInit();
private:
public:
	int m_nWindowID;
	IListener* m_pEditorApp;

	//
	std::vector<SmartPointer<IWorldObj>> m_vecSelectObjs;
	SmartPointer<IWorldObj> m_SelectObj;
	//
};

extern template  class EDITOR_API  Singleton<EditorApplication>;