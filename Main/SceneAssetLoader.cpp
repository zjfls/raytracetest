#include "stdafx.h"
#include "SceneAssetLoader.h"
#include "SingleResourceAsset.h"
#include "XmlPrefabLoader.h"
#include "tinyxml2.h"
#include "XmlSceneLoadHelper.h"
#include "SceneResource.h"
using namespace tinyxml2;

ZG::SceneAssetLoader::SceneAssetLoader()
{

}

ZG::SceneAssetLoader::~SceneAssetLoader()
{

}

IAsset* ZG::SceneAssetLoader::Load(string path, void* pArg /*= nullptr*/)
{
	SingleResourceAsset* pAsset = new SingleResourceAsset;
	m_pAsset = pAsset;
	//
	//
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
