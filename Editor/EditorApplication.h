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


		void	SetWindowID(int id);
		int		GetWindowID(){ return m_RenderViewInfo.m_bWindowed; };
		bool	AddView(int id, EditorRenderView*);
		bool	RemoveView(int id);
		void	UpdateGizemo();
		void	Run();
		//
		void	SaveScene(std::string fileName);
		void	LoadScene(std::string fileName);
		std::map<int, EditorRenderView*> m_ViewMap;
		virtual void SetupScene();
		virtual void NotifyListener(std::string msg, IListenerSubject* pSubject);
		//
		void	OnSelectChange(SmartPointer<IWorldObj> pObj);
		void	OnClickScene(SmartPointer<CameraBase> pCamera,SmartPointer<RenderView> pRenderView);
		
		virtual void OnInit();

		bool excuteCommond(ICommand* pCommand) override;
		bool undoCommond(ICommand* pCommond) override;
		bool redoCommond(ICommand* pCommond) override;
	private:
	public:
		int m_nWindowID;
		IListener* m_pEditorApp;

		//
		std::vector<SmartPointer<IWorldObj>> m_vecSelectObjs;
		SmartPointer<IWorldObj> m_SelectObj;
		//
		EOperationState m_eOperState;
		ESelectOperState m_eSelState;
		//
		SmartPointer<IWorld> m_pGizmoScene;
		bool m_bShowSkeletonGizmo;
	};

	extern template  class EDITOR_API  Singleton < EditorApplication > ;
}