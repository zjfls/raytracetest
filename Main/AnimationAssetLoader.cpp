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

bool ZG::AnimationAssetLoader::Save(IAsset* pAsset)
{
	AnimationAsset* pAniAsset = dynamic_cast<AnimationAsset*>(pAsset);
	//
	if (pAniAsset == nullptr)
	{
		return false;
	}
	std::vector<AnimationResource*> vecRes;
	pAniAsset->GetAllResource<AnimationResource>(vecRes);
	if (vecRes.size() == 0)
	{
		return false;
	}
	AnimationResource* pAniRes = vecRes[0];
	//
	tinyxml2::XMLDocument doc;
	doc.LinkEndChild(doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
	doc.LinkEndChild(doc.NewComment("material resource"));
	tinyxml2::XMLElement* root = doc.NewElement("AnimationTrack");
	root->SetAttribute("SkinAnimation", pAniRes->m_bIsSkinAnimation);
	root->SetAttribute("Version", "1.0.0");
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
				SaveTransformCurve(pCurve, pCurveElem,doc);
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
	
	return true;
	//
}

ZG::AnimationAssetLoader::AnimationAssetLoader()
{

}


//
void ZG::AnimationAssetLoader::SaveTransformCurve(AnimationCurve<stTransformData>* pCurve, tinyxml2::XMLElement* pElem, tinyxml2::XMLDocument& doc)
{
	pElem->SetAttribute("Type", "Transform");
	unsigned int nAniDataSize = pCurve->GetSize();
	float fMaxTime = 0.0f;
	pElem->SetAttribute("KeyFrameNums", nAniDataSize);
	for (int i = 0; i < nAniDataSize; ++i)
	{
		KeyFrame<stTransformData> kdata = pCurve->GetKeyFrame(i);
		tinyxml2::XMLElement* pKFElem = doc.NewElement("KeyFrame");
		pElem->InsertEndChild(pKFElem);

		pKFElem->SetAttribute("Index", i);
		pKFElem->SetAttribute("Time", kdata.m_fTime);
		if (kdata.m_fTime > fMaxTime)
		{
			fMaxTime = kdata.m_fTime;
		}

		Vector3 translate, rotation, scale;
		translate = kdata.m_KeyFrameData.m_vecTranslate;
		rotation = kdata.m_KeyFrameData.m_vecRotation;
		scale = kdata.m_KeyFrameData.m_vecScale;

		tinyxml2::XMLElement* pKFElemTrans = doc.NewElement("Translate");
		tinyxml2::XMLElement* pKFElemRot = doc.NewElement("Rotation");
		tinyxml2::XMLElement* pKFElemScale = doc.NewElement("Scale");
		pKFElem->InsertEndChild(pKFElemTrans);
		pKFElem->InsertEndChild(pKFElemRot);
		pKFElem->InsertEndChild(pKFElemScale);

		pKFElemTrans->SetAttribute("x", translate.m_fx);
		pKFElemTrans->SetAttribute("y", translate.m_fy);
		pKFElemTrans->SetAttribute("z", translate.m_fz);

		pKFElemRot->SetAttribute("x", rotation.m_fx);
		pKFElemRot->SetAttribute("y", rotation.m_fy);
		pKFElemRot->SetAttribute("z", rotation.m_fz);

		pKFElemScale->SetAttribute("x", scale.m_fx);
		pKFElemScale->SetAttribute("y", scale.m_fy);
		pKFElemScale->SetAttribute("z", scale.m_fz);
	}
	
}


