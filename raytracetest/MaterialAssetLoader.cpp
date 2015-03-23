#include "stdafx.h"
#include "MaterialAssetLoader.h"
#include "MaterialAsset.h"
#include "RasterMaterial.h"
#include "tinyxml2.h"
#include "ResourceMananger.h"
#include "TextureSampler.h"
#include "AssetManager.h"
using namespace tinyxml2;

MaterialAssetLoader::MaterialAssetLoader()
{
}


MaterialAssetLoader::~MaterialAssetLoader()
{
}

IAsset* MaterialAssetLoader::Load(string path, void* pArg /*= nullptr*/)
{
	MaterialAsset* pAsset = new MaterialAsset();
	pAsset->m_strPath = path;
	m_pAsset = pAsset;
	XMLDocument doc;
	doc.LoadFile(path.c_str());
	XMLElement* pElem = doc.FirstChildElement("Material");
	shared_ptr<RasterMaterial> pMatRes = dynamic_pointer_cast<RasterMaterial>(ResourceManager<MaterialResource>::GetInstance()->GetResource(path));
	if (pMatRes != nullptr)
	{
		pAsset->AddResource(path, pMatRes);
		return pAsset;
	}
	pMatRes = ResourceManager<MaterialResource>::GetInstance()->CreateResource<RasterMaterial>(path);
	pAsset->AddResource(path, pMatRes);
	XMLElement* pArgElem = pElem->FirstChildElement("MaterialArg");
	do 
	{
		string Name = pArgElem->Attribute("Name");
		string strArgType = pArgElem->Attribute("Type");
		MaterialArg* pArg = nullptr;
		if (pMatRes->m_matArgs.find(Name) != std::end(pMatRes->m_matArgs))
		{
			pArgElem = pArgElem->NextSiblingElement("MaterialArg");
			continue;
		}
		if (strArgType == "TextureSampler")
		{
			TMatArg<TextureSampler>* pSampArg = new TMatArg<TextureSampler>(EMATARGTYPESAMPLER);
			pSampArg->SetShaderType(EMATSHADERFRAG);

			XMLElement* pTextureElem = pArgElem->FirstChildElement("Texture");
			string texPath = pTextureElem->Attribute("RefPath");
			if (ResourceManager<Texture>::GetInstance()->GetResource(texPath) == nullptr)
			{
				AssetManager::GetInstance()->LoadAsset(texPath);
			}
			shared_ptr<Texture> pTexRes = ResourceManager<Texture>::GetInstance()->GetResource(texPath);
			if (pTexRes == nullptr)
			{
				AssetManager::GetInstance()->LoadAsset(texPath);
			}
			pSampArg->m_Data.m_pTexture = pTexRes;
			pArg = pSampArg;
		}
		pMatRes->m_matArgs[Name] = pArg;
		pArgElem = pArgElem->NextSiblingElement("MaterialArg");
	} while (pArgElem != nullptr);
	return pAsset;
}
