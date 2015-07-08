#include "stdafx.h"
#include "EditorModuleProperty.h"
#include "Transform.h"
#include "Vector3.h"
#include "Sphere3D.h"
#include <iostream>
#include <thread>
#include "RenderManager.h"
#include "RenderSystem.h"
#include "RenderView.h"
#include "SkeletonResource.h"
EditorModuleProperty::EditorModuleProperty()
{
}


EditorModuleProperty::~EditorModuleProperty()
{
}

void EditorModuleProperty::SetProperty(void* pData)
{
	//std::cout << "thread id:" << std::this_thread::get_id() << std::endl;
	const type_info& tinfo = typeid(*m_pModule.get());
	std::string className = tinfo.name();
	if (typeid(*m_pModule.get()) == typeid(Sphere3D))
	{
		SmartPointer<Sphere3D> pSphere = m_pModule.SmartPointerCast<Sphere3D>();
		if (m_PropName == "RADIUS")
		{
			pSphere->m_fRadius = *((float*)pData);
			pSphere->GeneratePolygon();
			//RenderManager::GetInstance()->GetDefaultRenderSystem->
		}
		if (m_PropName == "SUBDIVIDE")
		{
			pSphere->m_nSubdivide = *((int*)pData);
			pSphere->GeneratePolygon();
		}
	}
	if (typeid(*m_pModule.get()) == typeid(Transform))
	{
		SmartPointer<Transform> pTransform = m_pModule.SmartPointerCast<Transform>();
		if (m_PropName == "TRANSLATEX")
		{
			Vector3 pos = pTransform->GetLocalTranslate();
			pos.m_fx = *((float*)pData);
			pTransform->SetTranslate(pos);
		}
		if (m_PropName == "TRANSLATEY")
		{
			Vector3 pos = pTransform->GetLocalTranslate();
			pos.m_fy = *((float*)pData);
			pTransform->SetTranslate(pos);
		}
		if(m_PropName == "TRANSLATEZ")
		{
			Vector3 pos = pTransform->GetLocalTranslate();
			pos.m_fz = *((float*)pData);
			pTransform->SetTranslate(pos);
		}
		if (m_PropName == "ROTATIONX")
		{
			Vector3 rot = pTransform->GetRotation();
			rot.m_fx = *((float*)pData);
			pTransform->SetOrientation(rot.m_fx, rot.m_fy, rot.m_fz);
		}
		if (m_PropName == "ROTATIONY")
		{
			Vector3 rot = pTransform->GetRotation();
			rot.m_fy = *((float*)pData);
			pTransform->SetOrientation(rot.m_fx, rot.m_fy, rot.m_fz);
		}
		if (m_PropName == "ROTATIONZ")
		{
			Vector3 rot = pTransform->GetRotation();
			rot.m_fz = *((float*)pData);
			pTransform->SetOrientation(rot.m_fx, rot.m_fy, rot.m_fz);
		}
		if (m_PropName == "SCALEX")
		{
			Vector3 scale = pTransform->GetScale();
			scale.m_fx = *((float*)pData);
			pTransform->SetScale(scale.m_fx, scale.m_fy, scale.m_fz);
		}
		if (m_PropName == "SCALEY")
		{
			Vector3 scale = pTransform->GetScale();
			scale.m_fy = *((float*)pData);
			pTransform->SetScale(scale.m_fx, scale.m_fy, scale.m_fz);
		}
		if (m_PropName == "SCALEZ")
		{
			Vector3 scale = pTransform->GetScale();
			scale.m_fz = *((float*)pData);
			pTransform->SetScale(scale.m_fx, scale.m_fy, scale.m_fz);
		}
	}
}

void ZG::EditorModuleProperty::GetValue(void* pData)
{
	if (typeid(*m_pModule.get()) == typeid(Sphere3D))
	{
		SmartPointer<Sphere3D> pSphere = m_pModule.SmartPointerCast<Sphere3D>();
		if (m_PropName == "RADIUS")
		{
			pSphere->m_fRadius = *((float*)pData);
			pSphere->GeneratePolygon();
			//RenderManager::GetInstance()->GetDefaultRenderSystem->
		}
		if (m_PropName == "SUBDIVIDE")
		{
			pSphere->m_nSubdivide = *((int*)pData);
			pSphere->GeneratePolygon();
		}
	}
	if (typeid(*m_pModule.get()) == typeid(Transform))
	{
		SmartPointer<Transform> pTransform = m_pModule.SmartPointerCast<Transform>();
		if (m_PropName == "TRANSLATEX")
		{
			Vector3 pos = pTransform->GetLocalTranslate();
			*((float*)pData) = pos.m_fx;
		}
		if (m_PropName == "TRANSLATEY")
		{
			Vector3 pos = pTransform->GetLocalTranslate();
			*((float*)pData) = pos.m_fy;
		}
		if (m_PropName == "TRANSLATEZ")
		{
			Vector3 pos = pTransform->GetLocalTranslate();
			*((float*)pData) = pos.m_fz;
		}
		if (m_PropName == "ROTATIONX")
		{
			Vector3 rot = pTransform->GetRotation();
			*((float*)pData) = rot.m_fx;
		}
		if (m_PropName == "ROTATIONY")
		{
			Vector3 rot = pTransform->GetRotation();
			*((float*)pData) = rot.m_fy;
		}
		if (m_PropName == "ROTATIONZ")
		{
			Vector3 rot = pTransform->GetRotation();
			*((float*)pData) = rot.m_fz;
		}
		if (m_PropName == "SCALEX")
		{
			Vector3 scale = pTransform->GetScale();
			*((float*)pData) = scale.m_fx;
		}
		if (m_PropName == "SCALEY")
		{
			Vector3 scale = pTransform->GetScale();
			*((float*)pData) = scale.m_fy;
		}
		if (m_PropName == "SCALEZ")
		{
			Vector3 scale = pTransform->GetScale();
			*((float*)pData) = scale.m_fz;
		}
	}
}


