#pragma once
#include "Singleton.h"
#include "SmartPointer.h"
#include "GameObjectBase.h"


	namespace ZG
	{
		class IWorldObj;
		class IRenderable;
		class TranslateGizmo;
		class SkeletonModule;
		class MAIN_API GizmoManager :public Singleton<GizmoManager>, public GameObjectBase
		{
		public:
			GizmoManager();
			virtual ~GizmoManager();

			bool	Init();
			void	BuildSelectObj(SmartPointer<IWorldObj> pSelObj);
			IWorldObj* CreateSkeletonGizmo(SkeletonModule* pModule);
		private:
			void createTranlateGizmo();
			void createRotationGizmo();
			void createScaleGizmo();
			void createSceneGridGizmo();
		public:
			//
			SmartPointer<TranslateGizmo> m_pTranslateGizmo;
			//
			SmartPointer<IWorldObj>	 m_pSceneGrid;
			//
			SmartPointer<IWorldObj>	 m_pSelectObjWireFrame;
		};
		extern template  class MAIN_API  Singleton < GizmoManager >;
	}


