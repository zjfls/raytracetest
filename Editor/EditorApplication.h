#pragma once
#pragma once
#include "Singleton.h"
#include "ApplicationBase.h"
#include <map>
#include "IListenerSubject.h"
#include "IReceiver.h"
namespace ZG
{
	class IWorld;
	class IWorldObj;
	class EditorRenderView;
	class CameraBase;
	class EditorSceneView;
	//class RenderView;
	//
	class EDITOR_API EditorApplication :public ApplicationBase, public Singleton<EditorApplication>, public IListenerSubject,public IReceiver
	{
	public:
		enum EOperationState
		{
			EStateSelect,
			EStateTranslate,
			EStateRotate,
			EStateScale
		};
		enum ESelectOperState
		{
			ESelNone,
			ETranslateRight,
			ETranslateUp,
			ETranslateForward
		};
		EditorApplication();
		virtual ~EditorApplication();

		IWorldObj*	getSelectObj();
		void	SetWindowID(int id);
		int		GetWindowID(){ return m_RenderViewInfo.m_bWindowed; };
		bool	AddView(int id, EditorRenderView*);
		bool	RemoveView(int id);
		void	UpdateGizemo();
		void	Run();
		//
		void	SaveScene(std::string fileName);
		void	LoadScene(std::string fileName);
		
		virtual void SetupScene();
		virtual void NotifyListener(std::string msg, IListenerSubject* pSubject);
		//
		void	SelectChange(SmartPointer<IWorldObj> pObj);
		void	OnClickScene(SmartPointer<CameraBase> pCamera,SmartPointer<RenderView> pRenderView);
		EditorSceneView*	getActiveScene();
		virtual void OnInit();
		void OnClose() override;
		bool excuteCommond(ICommand* pCommand) override;
		bool undoCommond(ICommand* pCommond) override;
		bool redoCommond(ICommand* pCommond) override;
	private:
		SmartPointer<IWorldObj> m_SelectObj;
	public:
		int m_nWindowID;
		IListener* m_pEditorApp;
		std::map<int, EditorRenderView*> m_ViewMap;
		//
		std::vector<SmartPointer<IWorldObj>> m_vecSelectObjs;
		
		//
		EOperationState m_eOperState;
		ESelectOperState m_eSelState;
		//
		SmartPointer<IWorld> m_pGizmoScene;
		bool m_bShowSkeletonGizmo;
	};

	extern template  class EDITOR_API  Singleton < EditorApplication > ;
}