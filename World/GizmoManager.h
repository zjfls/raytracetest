#pragma once
#include "Singleton.h"
#include "SmartPointer.h"
#include "GameObjectBase.h"


	namespace ZG
	{
		class IWorldObj;
		class IRenderable;
		class TranslateGizmo;
		class WORLD_API GizmoManager :public Singleton<GizmoManager>, public GameObjectBase
		{
		public:
			GizmoManager();
			virtual ~GizmoManager();

			bool	Init();
			void	BuildSelectObj(SmartPointer<IWorldObj> pSelObj);
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
		extern template  class WORLD_API  Singleton < GizmoManager > ;
	}


