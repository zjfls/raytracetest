#include "stdafx.h"
#include "MaterialAssetLoader.h"
#include "MaterialAsset.h"
#include "RasterMaterial.h"
#include "tinyxml2.h"
#include "ResourceManager.h"
#include "TextureSampler.h"
#include "AssetManager.h"
#include "Texture.h"
#include "RenderPass.h"
#include "VertexShader.h"
#include "FragShader.h"
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
	while (pArgElem != nullptr)
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
	};
	XMLElement* pPassElem = pElem->FirstChildElement("RenderPass");
	while (pPassElem != nullptr)
	{
		string strName = pPassElem->Attribute("Name");
		string strBrdf = pPassElem->Attribute("BRDF");


		XMLElement* pVertexShader = pPassElem->FirstChildElement("VertexShader");
		XMLElement* pFragShader = pPassElem->FirstChildElement("FragElem");
		string vertShaderPath = pVertexShader->Attribute("refPath");
		string vertShaderType = pVertexShader->Attribute("ShaderType");
		string fragShaderPath = pFragShader->Attribute("refPath");
		string fragShaderType = pFragShader->Attribute("ShaderType");


		shared_ptr<VertexShader> pVSResource = ResourceManager<VertexShader>::GetInstance()->GetResource(vertShaderPath);
		if (pVSResource == nullptr)
		{
			AssetManager::GetInstance()->LoadAsset(vertShaderPath);
			pVSResource = ResourceManager<VertexShader>::GetInstance()->GetResource(vertShaderPath);
		}
		shared_ptr<FragShader> pFSResource = ResourceManager<FragShader>::GetInstance()->GetResource(fragShaderPath);
		if (pFSResource == nullptr)
		{
			AssetManager::GetInstance()->LoadAsset(fragShaderPath);
			pFSResource = ResourceManager<FragShader>::GetInstance()->GetResource(fragShaderPath);
		}

		RenderPass* pPass = new RenderPass;
		pMatRes->AddPass(strName,pPass);
		pPass->m_pVertexShader = pVSResource;
		pPass->m_pFragShader = pFSResource;
		if (vertShaderType == "Origin")
		{
			pPass->m_eVertexShaderType = EVERTEXSHADERORIGIN;
		}
		if (fragShaderType == "Origin")
		{
			pPass->m_eFragShaderType = EFRAGSHADERORIGIN;
		}
		pPassElem = pPassElem->NextSiblingElement("RenderPass");

	};
	return pAsset;
}
