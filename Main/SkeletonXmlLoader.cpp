#include "stdafx.h"
#include "SkeletonXmlLoader.h"
#include "SkeletonResource.h"
#include "IAsset.h"
#include "tinyxml2.h"
using namespace tinyxml2;



bool ZG::SkeletonXmlLoader::Save(IAsset* pAsset)
{
	if (pAsset == nullptr)
	{
		return false;
	}
	std::string path = pAsset->m_strPath;
	SkeletonResource* pSkeRes = pAsset->GetResource<SkeletonResource>();
	XMLDocument doc;
	//XMLDeclaration *declare = new XMLDeclaration("1.0");
	doc.LinkEndChild(doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
	doc.LinkEndChild(doc.NewComment("skeleton resource"));
	tinyxml2::XMLElement* pSkeInfo = doc.NewElement("Info");
	pSkeInfo->SetAttribute("BoneNum", pSkeRes->m_nBoneNum);
	doc.LinkEndChild(pSkeInfo);
	tinyxml2::XMLElement* pBoneRoot = doc.NewElement("Bone");
	doc.LinkEndChild(pBoneRoot);
	//PrefabProcessWorldObj(doc, pPrefab->m_pRoot, root);
	SkeletonProcessBone(doc, pSkeRes->m_pRoot, pBoneRoot);
	doc.SaveFile(path.c_str());
	return true;
}



IAsset* ZG::SkeletonXmlLoader::Load(std::string path, void* pArg /*= nullptr*/)
{
	return nullptr;
}

ZG::SkeletonXmlLoader::SkeletonXmlLoader()
{

}

ZG::SkeletonXmlLoader::~SkeletonXmlLoader()
{

}

void ZG::SkeletonXmlLoader::SkeletonProcessBone(tinyxml2::XMLDocument& doc, Bone* pBone, tinyxml2::XMLElement* pElem)
{
	if (pBone == nullptr && pElem == nullptr)
	{
		return;
	}
	pElem->SetAttribute("Name", pBone->m_strName.c_str());
	Vector3 t, r, s;
	t = pBone->t;
	r = pBone->r;
	s = pBone->s;
	XMLElement* pElemT = doc.NewElement("Translation");
	XMLElement* pElemS = doc.NewElement("Scale");
	XMLElement* pElemR = doc.NewElement("Rotation");
	pElem->LinkEndChild(pElemT);
	pElem->LinkEndChild(pElemR);
	pElem->LinkEndChild(pElemS);

	pElemT->SetAttribute("x", t.m_fx);
	pElemT->SetAttribute("y", t.m_fy);
	pElemT->SetAttribute("z", t.m_fz);

	pElemR->SetAttribute("x", r.m_fx);
	pElemR->SetAttribute("y", r.m_fy);
	pElemR->SetAttribute("z", r.m_fz);

	pElemS->SetAttribute("x", s.m_fx);
	pElemS->SetAttribute("y", s.m_fy);
	pElemS->SetAttribute("z", s.m_fz);

	for each (Bone* pChildBone in pBone->vecChild)
	{
		tinyxml2::XMLElement* pChild = doc.NewElement("Bone");
		pElem->LinkEndChild(pChild);
		SkeletonProcessBone(doc, pChildBone, pChild);
	}
}
