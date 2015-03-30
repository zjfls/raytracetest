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
	IWorldObj* pRoot = new IWorldObj;
	ProcessWorldObjElem(pElem, pRoot);

	//Prefab* pPrefab = new Prefab;
	//pPrefab->m_pRoot = pRoot;
	shared_ptr<PrefabResource> pPrefab = ResourceManager<PrefabResource>::GetInstance()->CreateResource<PrefabResource>(path);
	pPrefab->m_pRoot = pRoot;
	pPrefabAsset->AddResource(path, pPrefab);
	return pPrefabAsset;
}

void XmlPrefabLoader::ProcessWorldObjElem(XMLElement* pElem, IWorldObj* pObj) const
{
	//char temp[128];
	pObj->m_strName = pElem->Attribute("name");
	XMLElement* pChildElem = pElem->FirstChildElement();
	string name = pChildElem->Name();
	do
	{
		if (name == "Transform")
		{
			ProcessTransformElem(pChildElem, pObj);
		}
		else if (name == "Mesh")
		{
			ProcessMeshElem(pChildElem, pObj);
		}
		else if (name == "WorldObj")
		{
			IWorldObj* pChild = new IWorldObj;
			pObj->addChild(pChild);
			ProcessWorldObjElem(pChildElem, pChild);
		}
		pChildElem = pChildElem->NextSiblingElement();
	} while (pChildElem != nullptr);

}

void XmlPrefabLoader::ProcessTransformElem(tinyxml2::XMLElement* pElem, IWorldObj* pObj) const
{
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

	pTrans->QueryFloatAttribute("x", &t.m_fx);
	pTrans->QueryFloatAttribute("y", &t.m_fy);
	pTrans->QueryFloatAttribute("z", &t.m_fz);

	Transform* trans = pObj->m_pTransform;
	trans->SetTranslate(t);
	trans->SetScale(s.m_fx, s.m_fy, s.m_fz);
	trans->SetOrientation(r.m_fx, r.m_fy, r.m_fz);
}

void XmlPrefabLoader::ProcessMeshElem(tinyxml2::XMLElement* pElem, IWorldObj* pObj) const
{
	string path = pElem->Attribute("refPath");
	Mesh* pMesh = pObj->addModule<Mesh>();
	shared_ptr<MeshResource> pMeshRes = ResourceManager<MeshResource>::GetInstance()->GetResource(path);
	if (pMeshRes == nullptr)
	{
		AssetManager::GetInstance()->LoadAsset(path);
	}
	XMLElement* pMatElem = pElem->FirstChildElement("Material");
	string matpath = pMatElem->Attribute("refPath");
	shared_ptr<RasterMaterial> pMatRes = dynamic_pointer_cast<RasterMaterial>(ResourceManager<MaterialResource>::GetInstance()->GetResource(path));
	if (pMatRes == nullptr)
	{
		AssetManager::GetInstance()->LoadAsset(matpath);
	}
	pMesh->m_pSharedMaterial = pMatRes;


}
