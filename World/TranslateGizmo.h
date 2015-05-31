#pragma once
#include "GameObjectBase.h"
#include "MaterialResource.h"
namespace ZG
{
	class TranslateGizmo:public GameObjectBase
	{
	public:
		TranslateGizmo();
		virtual ~TranslateGizmo();


		//
		shared_ptr<IWorldObj> m_pRoot;
		shared_ptr<MaterialResource> m_pUpMaterialCylinder;
		shared_ptr<MaterialResource> m_pUpMaterialCone;
		shared_ptr<MaterialResource> m_pRightMaterialCylinder;
		shared_ptr<MaterialResource> m_pRightMaterialCone;
		shared_ptr<MaterialResource> m_pForwardMaterialCylinder;
		shared_ptr<MaterialResource> m_pForwardMaterialCone;
		friend class GizmoManager;
	};
}


