#include "stdafx.h"
#include "XmlPrefabLoader.h"
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

//extern template  class __declspec(dllimport) Singleton < ResourceManager<MeshResource> >;

using namespace tinyxml2;
XmlPrefabLoader::XmlPrefabLoader()
{
}


XmlPrefabLoader::~XmlPrefabLoader()
{
}

IAsset* XmlPrefabLoader::Load(string path, void* pArg /*= nullptr*/)
{
	PrefabAsset* pPrefabAsset = new PrefabAsset;
	pPrefabAsset->m_strPath = path;
	m_pAsset = pPrefabAsset;
	XMLDocument doc;
	doc.LoadFile(path.c_str());
	XMLElement* pElem = doc.FirstChildElement("WorldObj");
	SmartPointer<IWorldObj> pRoot = SmartPointer<IWorldObj>(new IWorldObj);
	ProcessWorldObjElem(pElem, pRoot);
	//Prefab* pPrefab = new Prefab;
	//pPrefab->m_pRoot = pRoot;
	SmartPointer<PrefabResource> pPrefab = ResourceManager<PrefabResource>::GetInstance()->CreateResource<PrefabResource>(path);
	pPrefab->m_pRoot = pRoot;
	pPrefabAsset->AddResource(path, pPrefab.get());
	pRoot->m_strName = getFileNameWithoutSuffix(path);
	return pPrefabAsset;
}

void XmlPrefabLoader::ProcessWorldObjElem(XMLElement* pElem, SmartPointer<IWorldObj> pObj) const
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
			ProcessTransformElem(pChildElem, pObj);
		}
		else if (name == "Mesh")
		{
			ProcessMeshElem(pChildElem, pObj);
		}
		else if (name == "WorldObj")
		{
			SmartPointer<IWorldObj> pChild = SmartPointer<IWorldObj>(new IWorldObj);
			pObj->addChild(pChild);
			ProcessWorldObjElem(pChildElem, pChild);
		}
		pChildElem = pChildElem->NextSiblingElement();
	} while (pChildElem != nullptr);

}

void XmlPrefabLoader::ProcessTransformElem(tinyxml2::XMLElement* pElem, SmartPointer<IWorldObj> pObj) const
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

void XmlPrefabLoader::ProcessMeshElem(tinyxml2::XMLElement* pElem, SmartPointer<IWorldObj> pObj) const
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

bool ZG::XmlPrefabLoader::Save(IAsset* pAsset)
{
	m_pAsset = pAsset;
	std::string path = pAsset->m_strPath;
	PrefabResource* pRes = pAsset->GetResource<PrefabResource>();
	if (pRes == nullptr)
	{
		return false;
	}
	XMLDocument doc;
	//XMLDeclaration *declare = new XMLDeclaration("1.0");
	doc.LinkEndChild(doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
	doc.LinkEndChild(doc.NewComment("prefab resource"));
	tinyxml2::XMLElement* root = doc.NewElement("WorldObj");
	doc.LinkEndChild(root);
	PrefabProcessWorldObj(doc, pRes->m_pRoot, root);
	doc.SaveFile(path.c_str());

	return true;
}

void ZG::XmlPrefabLoader::PrefabProcessWorldObj(tinyxml2::XMLDocument& doc, SmartPointer<IWorldObj> pObj, tinyxml2::XMLElement* elem)
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
			PrefabProcessTransformModule(doc, pTrans, pElemTrans);
			elem->LinkEndChild(pElemTrans);
			continue;
		}
		SmartPointer<Mesh> pMesh = pModule.SmartPointerCast<Mesh>();
		if (pMesh != nullptr)
		{
			XMLElement* pElementMesh = doc.NewElement("Mesh");
			PrefabProcessMeshModule(doc, pMesh, pElementMesh);
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
		PrefabProcessWorldObj(doc, pChild, pChildElem);
	}
}

void ZG::XmlPrefabLoader::PrefabProcessTransformModule(tinyxml2::XMLDocument& doc, SmartPointer<Transform> pTrans, tinyxml2::XMLElement* pElem)
{
	Vector3 translate = pTrans->GetLocalTranslate();
	Vector3 scale = pTrans->GetScale();
	Orientation ori = pTrans->GetOrientation();
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

	pElemR->SetAttribute("x", ori.m_vecEulerAngle.m_fx);
	pElemR->SetAttribute("y", ori.m_vecEulerAngle.m_fy);
	pElemR->SetAttribute("z", ori.m_vecEulerAngle.m_fz);

	pElemS->SetAttribute("x", scale.m_fx);
	pElemS->SetAttribute("y", scale.m_fy);
	pElemS->SetAttribute("z", scale.m_fz);
}

void ZG::XmlPrefabLoader::PrefabProcessMeshModule(tinyxml2::XMLDocument& doc, SmartPointer<Mesh> pMesh, tinyxml2::XMLElement* pElem)
{
	pElem->SetAttribute("refPath", pMesh->GetMeshResource()->GetRefPath().c_str());
	if (pMesh->m_pSharedMaterial == nullptr)
	{
		return;
	}
	XMLElement* pMatElem = doc.NewElement("Material");
	pElem->LinkEndChild(pMatElem);
	//pMatElem->SetAttribute("Name", "testmat");
	PrefabProcessMaterial(doc, pMesh->m_pSharedMaterial.SmartPointerCast<RasterMaterial>(), pMatElem);
}

void ZG::XmlPrefabLoader::PrefabProcessMaterial(tinyxml2::XMLDocument& doc, SmartPointer<RasterMaterial> pMaterial, tinyxml2::XMLElement* pElem)
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
