#include "stdafx.h"
#include "SceneAssetLoader.h"
#include "SingleResourceAsset.h"
#include "XmlPrefabLoader.h"
#include "tinyxml2.h"
#include "XmlSceneLoadHelper.h"
#include "SceneResource.h"
#include "IWorldObj.h"
using namespace tinyxml2;

ZG::SceneAssetLoader::SceneAssetLoader()
{

}

ZG::SceneAssetLoader::~SceneAssetLoader()
{

}

IAsset* ZG::SceneAssetLoader::Load(std::string path, void* pArg /*= nullptr*/)
{
	SingleResourceAsset* pAsset = new SingleResourceAsset;
	pAsset->m_strPath = path;
	m_pAsset = pAsset;
	XMLDocument doc;
	doc.LoadFile(path.c_str());
	XMLElement* pElem = doc.FirstChildElement("WorldObj");
	SmartPointer<IWorldObj> pRoot = new IWorldObj;
	XmlSceneLoadHelper::LoadWorldObjElem(pElem, pRoot);
	//Prefab* pPrefab = new Prefab;
	//pPrefab->m_pRoot = pRoot;
	SmartPointer<SceneResource> pScene = ResourceManager<SceneResource>::GetInstance()->CreateResource<SceneResource>(path);
	pScene->m_pRoot = pRoot;
	pAsset->AddResource(path, pScene.get());
	pRoot->m_strName = getFileNameWithoutSuffix(path);
	return pAsset;
}

bool ZG::SceneAssetLoader::Save(IAsset* pAsset)
{
	SceneResource* pRes = pAsset->GetResource<SceneResource>();
	if (pRes == nullptr)
	{
		return false;
	}
	XMLDocument doc;
	//XMLDeclaration *declare = new XMLDeclaration("1.0");
	doc.LinkEndChild(doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
	doc.LinkEndChild(doc.NewComment("scene resource"));
	tinyxml2::XMLElement* root = doc.NewElement("WorldObj");
	doc.LinkEndChild(root);
	XmlSceneLoadHelper::SaveProcessWorldObj(doc, pRes->m_pRoot, root);
	doc.SaveFile(pAsset->m_strPath.c_str());
	//
	return true;
}
