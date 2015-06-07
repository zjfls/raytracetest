#pragma once
#include "Singleton.h"
#include "SmartPointer.h"
#include "GameObjectBase.h"

class IWorldObj;
class IRenderable;
namespace ZG
{
	class TranslateGizmo;
	class WORLD_API GizmoManager:public Singleton<GizmoManager>,public ZG::GameObjectBase
	{
	public:
		GizmoManager();
		virtual ~GizmoManager();

		bool Init();
	private:
		void createTranlateGizmo();
		void createRotationGizmo();
		void createScaleGizmo();
		void createSceneGridGizmo();
	public:
		SmartPointer<TranslateGizmo> m_pTranslateGizmo;
		SmartPointer<IWorldObj>	 m_pSceneGrid;
	};
	extern template  class WORLD_API  Singleton<GizmoManager>;
}


