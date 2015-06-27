#pragma once
#include "GameObjectBase.h"
#include "MaterialResource.h"

namespace ZG
{

	class IWorldObj;
	class MaterialResource;
	class MAIN_API TranslateGizmo :public GameObjectBase
	{
	public:
		TranslateGizmo();
		virtual ~TranslateGizmo();


		//
		SmartPointer<IWorldObj> m_pRoot;
		SmartPointer<IWorldObj> m_pUp;
		SmartPointer<IWorldObj> m_pRight;
		SmartPointer<IWorldObj> m_pForward;
		SmartPointer<MaterialResource> m_pUpMaterialCylinder;
		SmartPointer<MaterialResource> m_pUpMaterialCone;
		SmartPointer<MaterialResource> m_pRightMaterialCylinder;
		SmartPointer<MaterialResource> m_pRightMaterialCone;
		SmartPointer<MaterialResource> m_pForwardMaterialCylinder;
		SmartPointer<MaterialResource> m_pForwardMaterialCone;
		friend class GizmoManager;
	};
}


