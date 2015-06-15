#include "stdafx.h"
#include "AnimationAssetLoader.h"
#include "AnimationAsset.h"
#include "tinyxml2.h"
#include "AnimationResource.h"
#include "AnimationCurve.h"
#include "Transform.h"
using namespace tinyxml2;

ZG::AnimationAssetLoader::~AnimationAssetLoader()
{

}

IAsset* ZG::AnimationAssetLoader::Load(string path, void* pArg /*= nullptr*/)
{
	AnimationAsset* pAsset = new AnimationAsset;
	return pAsset;
}

void ZG::AnimationAssetLoader::Save(IAsset* pAsset)
{
	AnimationAsset* pAniAsset = dynamic_cast<AnimationAsset*>(pAsset);
	//
	if (pAniAsset == nullptr)
	{
		return;
	}
	std::vector<AnimationResource*> vecRes;
	pAniAsset->GetAllResource<AnimationResource>(vecRes);
	if (vecRes.size() == 0)
	{
		return;
	}
	AnimationResource* pAniRes = vecRes[0];
	//
	tinyxml2::XMLDocument doc;
	doc.LinkEndChild(doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
	doc.LinkEndChild(doc.NewComment("material resource"));
	tinyxml2::XMLElement* root = doc.NewElement("Material");
	doc.InsertEndChild(root);
	for each (std::pair<std::string, SmartPointer<AnimationCurveBase>> p in pAniRes->m_mapCurves)
	{
		switch (p.second->getType())
		{
			case EANITRANSFORM:
			{
				AnimationCurve<stTransformData>* pCurve = dynamic_cast<AnimationCurve<stTransformData>*>(p.second.get());
				if (pCurve == nullptr)
				{
					std::cout << "animation curve save error!" << std::endl;
				}
				tinyxml2::XMLElement* pCurveElem = doc.NewElement("AnimationCurve");
				pCurveElem->SetAttribute("Name", p.first.c_str());
				SaveTransformCurve(pCurve, pCurveElem);
				std::cout << "add Curve:" << p.first.c_str() << std::endl;
				root->InsertEndChild(pCurveElem);
				//pCurElem->SetAttribute("Index",p.second)
			}
			break;
			default:
			break;
		}
	}
	doc.SaveFile(pAniRes->GetRefPath().c_str());
	

	//
}

ZG::AnimationAssetLoader::AnimationAssetLoader()
{

}


//
void ZG::AnimationAssetLoader::SaveTransformCurve(AnimationCurve<stTransformData>* pCurve, tinyxml2::XMLElement* pElem)
{

}


