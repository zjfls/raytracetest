#pragma once
#include "GameObjectBase.h"
#include "MaterialResource.h"
class IWorldObj;
class MaterialResource;
namespace ZG
{
	class TranslateGizmo:public GameObjectBase
	{
	public:
		TranslateGizmo();
		virtual ~TranslateGizmo();


		//
		SmartPointer<IWorldObj> m_pRoot;
		SmartPointer<MaterialResource> m_pUpMaterialCylinder;
		SmartPointer<MaterialResource> m_pUpMaterialCone;
		SmartPointer<MaterialResource> m_pRightMaterialCylinder;
		SmartPointer<MaterialResource> m_pRightMaterialCone;
		SmartPointer<MaterialResource> m_pForwardMaterialCylinder;
		SmartPointer<MaterialResource> m_pForwardMaterialCone;
		friend class GizmoManager;
	};
}


