#pragma once
#include "Singleton.h"
#include "SmartPointer.h"
#include "GameObjectBase.h"

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
	public:
		SmartPointer<TranslateGizmo> m_pTranslateGizmo;
	};
	extern template  class WORLD_API  Singleton<GizmoManager>;
}

