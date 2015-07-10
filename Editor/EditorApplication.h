#pragma once
#pragma once
#include "Singleton.h"
#include "ApplicationBase.h"
#include <map>
#include "IListenerSubject.h"
#include "IReceiver.h"
#include "Vector3.h"
#include <vector>
namespace ZG
{
	class IWorld;
	class IWorldObj;
	class EditorRenderView;
	class CameraBase;
	class EditorSceneView;
	struct EditorState
	{
		//
		Vector3 m_vecPressPos;
	};
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
		void	SelectionsChange(std::vector<IWorldObj*> vecObjs);
		void	AddSelection(IWorldObj* pObj);
		void	RemoveSelection(IWorldObj* pObj);
		void	SelectChange(SmartPointer<IWorldObj> pObj);
		void	ClearSelection();
		Vector3 GetSelectionsWorldTranslate();
		unsigned int GetSelectionCount();
		IWorldObj* GetSelectionByIndex(int index);

		////////////////////////////////////////////////////////////////////////////
		void	OnClickScene(SmartPointer<CameraBase> pCamera,SmartPointer<RenderView> pRenderView);
		EditorSceneView*	getActiveScene();
		virtual void OnInit();
		void OnClose() override;
		bool excuteCommond(ICommand* pCommand) override;
		bool undoCommond(ICommand* pCommond) override;
		bool redoCommond(ICommand* pCommond) override;
		///////////////////////////////////////////
		void StartTranslate();
		void EndTranslate();
	private:
		void	NotifySelectionChange();
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
	private:
		EditorState m_EditorState;
	};

	extern template  class EDITOR_API  Singleton < EditorApplication > ;
}