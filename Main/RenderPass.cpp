#include "stdafx.h"
#include "RenderPass.h"
#include "RasterMaterial.h"
#include "RasterRender.h"
#include "RenderSystem.h"
#include "HardwareVertexBuffer.h"
#include "HardwareIndexBuffer.h"
#include "HardwareVertexShader.h"
#include "HardwareFragShader.h"
#include "VertexShader.h"
#include "FragShader.h"
#include "IRenderable.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"
#include "Color.h"
#include "TextureSampler.h"
RenderPass::RenderPass()
{
}


RenderPass::~RenderPass()
{
}

void RenderPass::Render(RasterRender* pRender, IRenderable* pRenderable, ESTAGESHADERTYPE eStageShaderType, const RenderStateCollection& mapStates)
{
	shared_ptr<RasterMaterial> pMat = dynamic_pointer_cast<RasterMaterial>(pRenderable->m_pSharedMaterial);

	HardwareIndexBuffer* pIndexBuff = pRender->m_pRenderSystem->GetHardwareIndexBuffer(pRenderable->m_pIndexData);
	HardwareVertexBuffer* pVertexBuff = pRender->m_pRenderSystem->GetHardwareVertexBuffer(pRenderable->m_pVertexData);



	//
	VertexShaderDesc vsdesc;
	vsdesc.m_pVertexShader = m_pVertexShader;
	vsdesc.m_eStageDesc = eStageShaderType;
	vsdesc.m_eVShaderDesc = m_eVertexShaderType;
	HardwareVertexShader* pVertexShader = pRender->m_pRenderSystem->GetHardwareVertexShader(vsdesc);
	FragShaderDesc fsDesc;
	fsDesc.m_eStageDesc = eStageShaderType;
	fsDesc.m_eFragShaderDesc = m_eFragShaderType;
	fsDesc.m_pFragShader = m_pFragShader;
	HardwareFragShader* pFragShader = pRender->m_pRenderSystem->GetHardwareFragShader(fsDesc);
	//
	pRender->SetVertexShader(pVertexShader);
	pRender->SetFragShader(pFragShader);
	
	//
	BuildShaderArgs(pRender, pRenderable, eStageShaderType);
	//
	SetPassStates(pRender, mapStates);
	//
	SetShaderArgs(pRender, pMat, pVertexShader, pFragShader);
	

}

void RenderPass::BuildShaderArgs(RasterRender* pRender, IRenderable* pRenderabl, ESTAGESHADERTYPE eShaderType)
{

}

void RenderPass::SetPassStates(RasterRender* pRender, const RenderStateCollection& mapStates)
{

}
void RenderPass::SetShaderArgs(RasterRender* pRender, shared_ptr<RasterMaterial> pMaterial, HardwareVertexShader* pVertexShader, HardwareFragShader* pFragShader)
{
	std::map<string,MaterialArg*> mapTotalArg;
	for each (std::pair<string, MaterialArg*> p in pMaterial->m_matArgs)
	{
		mapTotalArg[p.first] = p.second;
	}
	for each (std::pair<string, MaterialArg*> p in m_ShaderArgs)
	{
		mapTotalArg[p.first] = p.second;
	}
	int nSamplerIndex = 0;
	//int nFragSamplerIndex = 0;
	
	for each (std::pair<string, MaterialArg*> p in mapTotalArg)
	{
		switch (p.second->m_EType)
		{
			case	EMATARGTYPEFLOAT1:
			{
				float* fValue = p.second->GetData<float>();
				if (EMATSHADERVERTE & p.second->m_EShaderType)
				{
					pVertexShader->SetFloat(p.first, *fValue);
				}
				if (EMATSHADERFRAG & p.second->m_EShaderType)
				{
					pFragShader->SetFloat(p.first, *fValue);
				}
			}
			break;
			case	EMATARGTYPEFLOAT4:
			{
				Vector4* vecValue = p.second->GetData<Vector4>();
				if (EMATSHADERVERTE & p.second->m_EShaderType)
				{
					pVertexShader->SetVector(p.first, *vecValue);
				}
				if (EMATSHADERFRAG & p.second->m_EShaderType)
				{
					pFragShader->SetVector(p.first, *vecValue);
				}
			}
			break;
			case	EMATARGTYPECOLOR:
			{
				Color* colorValue = p.second->GetData<Color>();
				Vector4 vecColor = Vector4(colorValue->m_fR,colorValue->m_fG,colorValue->m_fB,colorValue->m_fB);
				if (EMATSHADERVERTE & p.second->m_EShaderType)
				{
					pVertexShader->SetVector(p.first,vecColor);
				}
				if (EMATSHADERFRAG & p.second->m_EShaderType)
				{
					pFragShader->SetVector(p.first, vecColor);
				}
			}
			break;
			case	EMATARGTYPEINT:
			{
				int* nValue = p.second->GetData<int>();
				if (EMATSHADERVERTE & p.second->m_EShaderType)
				{
					pVertexShader->SetInt(p.first, *nValue);
				}
				if (EMATSHADERFRAG & p.second->m_EShaderType)
				{
					pFragShader->SetInt(p.first, *nValue);
				}
			}
			break;
			case EMATARGMATRIX:
			{
				Matrix44* pMat = p.second->GetData<Matrix44>();
				if (EMATSHADERVERTE & p.second->m_EShaderType)
				{
					pVertexShader->SetMatrix(p.first, *pMat);
				}
				if (EMATSHADERFRAG & p.second->m_EShaderType)
				{
					pFragShader->SetMatrix(p.first, *pMat);
				}
			}
			case	EMATARGTYPESAMPLER:
			{
				TextureSampler* pSampler = p.second->GetData<TextureSampler>();
				HardwareTexture* pHardwareTex = pRender->m_pRenderSystem->GetHardwareTexture(pSampler->m_pTexture);
				if (EMATSHADERVERTE & p.second->m_EShaderType || EMATSHADERFRAG & p.second->m_EShaderType)
				{
					pRender->SetTexture(nSamplerIndex, pHardwareTex);
					nSamplerIndex++;
				}
			}
			break;
			default:
			{

			}
			break;
		}
	}
}
