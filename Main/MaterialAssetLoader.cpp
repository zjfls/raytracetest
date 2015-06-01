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
#include "MaterialPass.h"
using namespace ZG;
using namespace tinyxml2;

MaterialAssetLoader::MaterialAssetLoader()
{
}


MaterialAssetLoader::~MaterialAssetLoader()
{
}

bool stringcompare(const char* a, const char* b)
{
	int na = strlen(a);
	int nb = strlen(b);
	if (na != nb)
	{
		return false;
	}
	for (int i = 0; i < na; ++i)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	return true;
}

IAsset* MaterialAssetLoader::Load(string path, void* pArg /*= nullptr*/)
{
	MaterialAsset* pAsset = new MaterialAsset();
	pAsset->m_strPath = path;
	m_pAsset = pAsset;
	XMLDocument doc;
	doc.LoadFile(path.c_str());
	XMLElement* pElem = doc.FirstChildElement("Material");
	SmartPointer<RasterMaterial> pMatRes = ResourceManager<MaterialResource>::GetInstance()->GetResource(path).SmartPointerCast<RasterMaterial>();
	if (pMatRes != nullptr)
	{
		pAsset->AddResource(path, pMatRes.get());
		return pAsset;
	}
	pMatRes = ResourceManager<MaterialResource>::GetInstance()->CreateResource<RasterMaterial>(path);
	pAsset->AddResource(path, pMatRes.get());
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
			SmartPointer<Texture> pTexRes = ResourceManager<Texture>::GetInstance()->GetResource(texPath);
			if (pTexRes == nullptr)
			{
				AssetManager::GetInstance()->LoadAsset(texPath);
			}
			pSampArg->m_Data.m_pTexture = pTexRes;
			pArg = pSampArg;
			if (Name == "NormalMap")
			{
				pSampArg->m_Data.m_eTextureUseType = ETU_NORMAL;
			}
		}
		pMatRes->m_matArgs[Name] = pArg;
		pArgElem = pArgElem->NextSiblingElement("MaterialArg");
	};
	XMLElement* pPassElem = pElem->FirstChildElement("RenderPass");
	while (pPassElem != nullptr)
	{
		MaterialPass* pPass = new MaterialPass;
		//
		XMLElement* pPassStateElem = pPassElem->FirstChildElement("PassState");
		if (pPassStateElem != nullptr)
		{
			XMLElement* pStateElem = pPassStateElem->FirstChildElement("State");
			while (pStateElem != nullptr)
			{
				std::string name = pStateElem->Attribute("Name");
				if (name == "AlphaTest")
				{
					bool value = pStateElem->BoolAttribute("Value");
					stRenderState state;
					state.m_eRenderState = ALPHATEST;
					state.m_nValue = value;
					pPass->m_vecRenderState.push_back(state);

				}
				else if (name == "AlphaBlend")
				{
					bool value = pStateElem->BoolAttribute("Value");
					stRenderState state;
					state.m_eRenderState = ALPHABLEND;
					state.m_nValue = value;
					pPass->m_vecRenderState.push_back(state);
				}
				else if (name == "AlphaTestRef")
				{
					int value = pStateElem->IntAttribute("Value");
					stRenderState state;
					state.m_eRenderState = ALPHATESTREF;
					state.m_nValue = value;
					pPass->m_vecRenderState.push_back(state);
				}
				pStateElem = pStateElem->NextSiblingElement("State");
			}
		}
		//
		string strName = pPassElem->Attribute("Name");
		string strBrdf = pPassElem->Attribute("BRDF");


		XMLElement* pVertexShader = pPassElem->FirstChildElement("VertexShader");
		XMLElement* pFragShader = pPassElem->FirstChildElement("FragElem");
		string vertShaderPath = pVertexShader->Attribute("refPath");
		string vertShaderType = pVertexShader->Attribute("ShaderType");
		string fragShaderPath = pFragShader->Attribute("refPath");
		string fragShaderType = pFragShader->Attribute("ShaderType");


		SmartPointer<VertexShader> pVSResource = ResourceManager<VertexShader>::GetInstance()->GetResource(vertShaderPath);
		if (pVSResource == nullptr)
		{
			AssetManager::GetInstance()->LoadAsset(vertShaderPath);
			pVSResource = ResourceManager<VertexShader>::GetInstance()->GetResource(vertShaderPath);
		}
		SmartPointer<FragShader> pFSResource = ResourceManager<FragShader>::GetInstance()->GetResource(fragShaderPath);
		//fragShaderPath = "./data/shader/SurfaceSpec.srf";
		if (pFSResource == nullptr)
		{
			AssetManager::GetInstance()->LoadAsset(fragShaderPath);
			pFSResource = ResourceManager<FragShader>::GetInstance()->GetResource(fragShaderPath);
		}

		
		pMatRes->AddPass(strName,pPass);
		pPass->m_pVertexShader = pVSResource;
		pPass->m_pFragShader = pFSResource;
		if (vertShaderType == "Origin")
		{
			pPass->m_eVertexShaderType = EVERTEXSHADERORIGIN;
		}
		else if (vertShaderType == "Auto")
		{
			pPass->m_eVertexShaderType = EVERTEXSHADERAUTO;
		}

		string srf = "Surface";
		if (fragShaderType == "Origin")
		{
			pPass->m_eFragShaderType = EFRAGSHADERORIGIN;
			//pPass->m_eFragShaderType = EFRAGSHADERSURFACE;
		}
		else if (fragShaderType == "Surface")
		{
			pPass->m_eFragShaderType = EFRAGSHADERSURFACE;
		}


	
		pPassElem = pPassElem->NextSiblingElement("RenderPass");

	};
	return pAsset;
}
