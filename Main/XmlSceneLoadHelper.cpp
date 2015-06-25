#include "stdafx.h"
#include "XmlSceneLoadHelper.h"
#include "tinyxml2.h"
#include "PrefabAsset.h"
#include "tinyxml2.h"
#include "IWorldObj.h"
#include "Mesh.h"
#include "MeshResource.h"
#include "ResourceManager.h"
#include "AssetManager.h"
#include "PrefabResource.h"
#include "RasterMaterial.h"
#include "FilePath.h"
#include "MaterialResource.h"
#include "Transform.h"
#include "MeshResource.h"
#include "RasterMaterial.h"
using namespace tinyxml2;

XmlSceneLoadHelper::XmlSceneLoadHelper()
{
}


XmlSceneLoadHelper::~XmlSceneLoadHelper()
{
}


void XmlSceneLoadHelper::LoadWorldObjElem(XMLElement* pElem, SmartPointer<IWorldObj> pObj)
{
	//char temp[128];
	pObj->m_strName = pElem->Attribute("name");
	XMLElement* pChildElem = pElem->FirstChildElement();
	do
	{
		string name = pChildElem->Name();
		if (name == "Transform")
		{
			//std::cout << pElem->Name() << ":" << pElem->Attribute("name") << std::endl;
			LoadTransformElem(pChildElem, pObj);
		}
		else if (name == "Mesh")
		{
			LoadMeshElem(pChildElem, pObj);
		}
		else if (name == "WorldObj")
		{
			SmartPointer<IWorldObj> pChild = SmartPointer<IWorldObj>(new IWorldObj);
			pObj->addChild(pChild);
			LoadWorldObjElem(pChildElem, pChild);
		}
		pChildElem = pChildElem->NextSiblingElement();
	} while (pChildElem != nullptr);

}

void XmlSceneLoadHelper::LoadTransformElem(tinyxml2::XMLElement* pElem, SmartPointer<IWorldObj> pObj)
{
	//XMLElement* pTransform = pElem->FirstChildElement("Transform");
	XMLElement* pTrans = pElem->FirstChildElement("Translation");
	XMLElement* pRot = pElem->FirstChildElement("Rotation");
	XMLElement* pScale = pElem->FirstChildElement("Scale");
	Vector3 t, r, s;
	pTrans->QueryFloatAttribute("x", &t.m_fx);
	pTrans->QueryFloatAttribute("y", &t.m_fy);
	pTrans->QueryFloatAttribute("z", &t.m_fz);

	pRot->QueryFloatAttribute("x", &r.m_fx);
	pRot->QueryFloatAttribute("y", &r.m_fy);
	pRot->QueryFloatAttribute("z", &r.m_fz);

	pScale->QueryFloatAttribute("x", &s.m_fx);
	pScale->QueryFloatAttribute("y", &s.m_fy);
	pScale->QueryFloatAttribute("z", &s.m_fz);

	SmartPointer<Transform> trans = pObj->m_pTransform;
	trans->SetTranslate(t);
	trans->SetScale(s.m_fx, s.m_fy, s.m_fz);
	trans->SetOrientation(r.m_fx, r.m_fy, r.m_fz);
}

void XmlSceneLoadHelper::LoadMeshElem(tinyxml2::XMLElement* pElem, SmartPointer<IWorldObj> pObj)
{
	string path = pElem->Attribute("refPath");
	SmartPointer<Mesh> pMesh = pObj->addModule<Mesh>();
	SmartPointer<MeshResource> pMeshRes = ResourceManager<MeshResource>::GetInstance()->GetResource(path);
	if (pMeshRes == nullptr)
	{
		AssetManager::GetInstance()->LoadAsset(path);
	}
	pMeshRes = ResourceManager<MeshResource>::GetInstance()->GetResource(path);
	XMLElement* pMatElem = pElem->FirstChildElement("Material");
	if (pMatElem != nullptr)
	{
		string matpath = pMatElem->Attribute("refPath");
		SmartPointer<RasterMaterial> pMatRes = ResourceManager<MaterialResource>::GetInstance()->GetResource(matpath).SmartPointerCast<RasterMaterial>();
		if (pMatRes == nullptr)
		{
			AssetManager::GetInstance()->LoadAsset(matpath);
		}
		pMatRes = ResourceManager<MaterialResource>::GetInstance()->GetResource(matpath).SmartPointerCast<RasterMaterial>();
		pMesh->m_pSharedMaterial = pMatRes.get();
	}
	pMesh->SetMeshResource(pMeshRes);


}



void ZG::XmlSceneLoadHelper::LoadProcessWorldObj(tinyxml2::XMLDocument& doc, SmartPointer<IWorldObj> pObj, tinyxml2::XMLElement* elem)
{
	if (pObj == nullptr || elem == nullptr)
	{
		return;
	}
	elem->SetAttribute("name", pObj->m_strName.c_str());
	unsigned int nModuleCount = pObj->GetModuleCount();
	for (unsigned int i = 0; i < nModuleCount; ++i)
	{
		SmartPointer<ModuleBase> pModule = pObj->GetModule(i);
		SmartPointer<Transform> pTrans = pModule.SmartPointerCast<Transform>();
		if (pTrans != nullptr)
		{
			XMLElement* pElemTrans = doc.NewElement("Transform");
			LoadProcessTransformModule(doc, pTrans, pElemTrans);
			elem->LinkEndChild(pElemTrans);
			continue;
		}
		SmartPointer<Mesh> pMesh = pModule.SmartPointerCast<Mesh>();
		if (pMesh != nullptr)
		{
			XMLElement* pElementMesh = doc.NewElement("Mesh");
			LoadProcessMeshModule(doc, pMesh, pElementMesh);
			elem->LinkEndChild(pElementMesh);

			continue;
		}

	}

	unsigned int nChildCount = pObj->GetChildCount();
	for (unsigned int i = 0; i < nChildCount; ++i)
	{
		SmartPointer<IWorldObj> pChild = pObj->GetChild(i);
		XMLElement* pChildElem = doc.NewElement("WorldObj");
		elem->LinkEndChild(pChildElem);
		LoadProcessWorldObj(doc, pChild, pChildElem);
	}
}

void ZG::XmlSceneLoadHelper::LoadProcessTransformModule(tinyxml2::XMLDocument& doc, SmartPointer<Transform> pTrans, tinyxml2::XMLElement* pElem)
{
	Vector3 translate = pTrans->GetLocalTranslate();
	Vector3 scale = pTrans->GetScale();
	Vector3 ori = pTrans->GetRotation();
	XMLElement* pElemT = doc.NewElement("Translation");
	XMLElement* pElemS = doc.NewElement("Scale");
	XMLElement* pElemR = doc.NewElement("Rotation");
	pElem->LinkEndChild(pElemT);
	pElem->LinkEndChild(pElemR);
	pElem->LinkEndChild(pElemS);
	//
	pElemT->SetAttribute("x", translate.m_fx);
	pElemT->SetAttribute("y", translate.m_fy);
	pElemT->SetAttribute("z", translate.m_fz);

	pElemR->SetAttribute("x", ori.m_fx);
	pElemR->SetAttribute("y", ori.m_fy);
	pElemR->SetAttribute("z", ori.m_fz);

	pElemS->SetAttribute("x", scale.m_fx);
	pElemS->SetAttribute("y", scale.m_fy);
	pElemS->SetAttribute("z", scale.m_fz);
}

void ZG::XmlSceneLoadHelper::LoadProcessMeshModule(tinyxml2::XMLDocument& doc, SmartPointer<Mesh> pMesh, tinyxml2::XMLElement* pElem)
{
	pElem->SetAttribute("refPath", pMesh->GetMeshResource()->GetRefPath().c_str());
	if (pMesh->m_pSharedMaterial == nullptr)
	{
		return;
	}
	XMLElement* pMatElem = doc.NewElement("Material");
	pElem->LinkEndChild(pMatElem);
	//pMatElem->SetAttribute("Name", "testmat");
	LoadProcessMaterial(doc, pMesh->m_pSharedMaterial.SmartPointerCast<RasterMaterial>(), pMatElem);
}

void ZG::XmlSceneLoadHelper::LoadProcessMaterial(tinyxml2::XMLDocument& doc, SmartPointer<RasterMaterial> pMaterial, tinyxml2::XMLElement* pElem)
{
	pElem->SetAttribute("refPath", pMaterial->GetRefPath().c_str());
	for each (std::pair<string, MaterialArg*> pair in pMaterial->m_matArgs)
	{
		switch (pair.second->m_EType)
		{
			case EMATARGTYPESAMPLER:
			{
				//XMLElement* pElemSamp = doc.NewElement("Sampler");
				//pElemSamp->SetAttribute("Name", pair.first.c_str());

				//TextureSampler* pTexSampler = pair.second->GetData<TextureSampler>();
				//pElemSamp->SetAttribute("Ref", pTexSampler->m_pTexture->GetRefPath().c_str());
				//pElem->LinkEndChild(pElemSamp);
			}
			break;
			default:
			break;
		}
	}
}

void ZG::XmlSceneLoadHelper::SaveProcessWorldObj(tinyxml2::XMLDocument& doc, SmartPointer<IWorldObj> pObj, tinyxml2::XMLElement* elem)
{
	if (pObj == nullptr || elem == nullptr)
	{
		return;
	}
	elem->SetAttribute("name", pObj->m_strName.c_str());
	unsigned int nModuleCount = pObj->GetModuleCount();
	for (unsigned int i = 0; i < nModuleCount; ++i)
	{
		SmartPointer<ModuleBase> pModule = pObj->GetModule(i);
		SmartPointer<Transform> pTrans = pModule.SmartPointerCast<Transform>();
		if (pTrans != nullptr)
		{
			XMLElement* pElemTrans = doc.NewElement("Transform");
			SaveProcessTransformModule(doc, pTrans, pElemTrans);
			elem->LinkEndChild(pElemTrans);
			continue;
		}
		SmartPointer<Mesh> pMesh = pModule.SmartPointerCast<Mesh>();
		if (pMesh != nullptr)
		{
			XMLElement* pElementMesh = doc.NewElement("Mesh");
			SaveProcessMeshModule(doc, pMesh, pElementMesh);
			elem->LinkEndChild(pElementMesh);

			continue;
		}

	}

	unsigned int nChildCount = pObj->GetChildCount();
	for (unsigned int i = 0; i < nChildCount; ++i)
	{
		SmartPointer<IWorldObj> pChild = pObj->GetChild(i);
		XMLElement* pChildElem = doc.NewElement("WorldObj");
		elem->LinkEndChild(pChildElem);
		SaveProcessWorldObj(doc, pChild, pChildElem);
	}
}

void ZG::XmlSceneLoadHelper::SaveProcessMeshModule(tinyxml2::XMLDocument& doc, SmartPointer<Mesh> pMesh, tinyxml2::XMLElement* pElem)
{
	pElem->SetAttribute("refPath", pMesh->GetMeshResource()->GetRefPath().c_str());
	if (pMesh->m_pSharedMaterial == nullptr)
	{
		return;
	}
	XMLElement* pMatElem = doc.NewElement("Material");
	pElem->LinkEndChild(pMatElem);
	//pMatElem->SetAttribute("Name", "testmat");
	SaveProcessMaterial(doc, pMesh->m_pSharedMaterial.SmartPointerCast<RasterMaterial>(), pMatElem);
}

void ZG::XmlSceneLoadHelper::SaveProcessTransformModule(tinyxml2::XMLDocument& doc, SmartPointer<Transform> pTrans, tinyxml2::XMLElement* pElem)
{
	Vector3 translate = pTrans->GetLocalTranslate();
	Vector3 scale = pTrans->GetScale();
	Vector3 rotation = pTrans->GetRotation();
	XMLElement* pElemT = doc.NewElement("Translation");
	XMLElement* pElemS = doc.NewElement("Scale");
	XMLElement* pElemR = doc.NewElement("Rotation");
	pElem->LinkEndChild(pElemT);
	pElem->LinkEndChild(pElemR);
	pElem->LinkEndChild(pElemS);
	//
	pElemT->SetAttribute("x", translate.m_fx);
	pElemT->SetAttribute("y", translate.m_fy);
	pElemT->SetAttribute("z", translate.m_fz);

	pElemR->SetAttribute("x", rotation.m_fx);
	pElemR->SetAttribute("y", rotation.m_fy);
	pElemR->SetAttribute("z", rotation.m_fz);

	pElemS->SetAttribute("x", scale.m_fx);
	pElemS->SetAttribute("y", scale.m_fy);
	pElemS->SetAttribute("z", scale.m_fz);
	//
}

void ZG::XmlSceneLoadHelper::SaveProcessMaterial(tinyxml2::XMLDocument& doc, SmartPointer<RasterMaterial> pMaterial, tinyxml2::XMLElement* pElem)
{
	pElem->SetAttribute("refPath", pMaterial->GetRefPath().c_str());
	for each (std::pair<string, MaterialArg*> pair in pMaterial->m_matArgs)
	{
		switch (pair.second->m_EType)
		{
			case EMATARGTYPESAMPLER:
			{
				//XMLElement* pElemSamp = doc.NewElement("Sampler");
				//pElemSamp->SetAttribute("Name", pair.first.c_str());

				//TextureSampler* pTexSampler = pair.second->GetData<TextureSampler>();
				//pElemSamp->SetAttribute("Ref", pTexSampler->m_pTexture->GetRefPath().c_str());
				//pElem->LinkEndChild(pElemSamp);
			}
			break;
			default:
			break;
		}
	}
}
